#include "server.h"
#include <QHostAddress>
#include <QDebug>
#include <QDataStream>
#include "nachrichtenformat.h"
#include <QStringList>
#include <QNetworkDatagram>

server::server(QObject *parent)
    : networkManager(parent)
{}

void server::handleServerError()
{
    emit serverErrorOccurred(srv1->errorString());
}

//method is called with signal-slot from gui when start button is clicked
void server::startServer(quint16 port)
{
    udp_socket = new QUdpSocket(this); //NEW for udp discovery
    udp_socket->bind(QHostAddress::Any, port, QUdpSocket::ShareAddress);
    connect(udp_socket, &QUdpSocket::readyRead, this, &server::handleUdpInquiry);

    srv1 = new QTcpServer(this);
    srv1->setMaxPendingConnections(10); //allowed to connect multiple clients for further functionalities (chat etc.)
    connect(srv1, &QTcpServer::newConnection, this, &server::newClientConnection);
    connect(srv1, &QTcpServer::acceptError, this, &server::handleServerError);

    if (srv1->listen(QHostAddress::Any, port) && srv1->serverPort() != 0) {
        qDebug() << "Server has started. Listening to port " + QString::number(srv1->serverPort()) + ".";
        emit serverStarted();
    } else {
        qDebug() << "Server failed to start. Error: " + srv1->errorString();
        handleServerError();
    }
}

//respond here if a udp datagram reaches the server back with GROUP5, called automatically if there's something to read with signal-slot readyRead
void server::handleUdpInquiry() {
    QString pwd = "TUM";
    QByteArray response = "GROUP5";

    while(udp_socket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udp_socket->receiveDatagram();
        if (pwd == QString::fromUtf8(datagram.data())) {
            qDebug() << "Server received datagram <TUM> from client. Sending datagram <GROUP5> back.";
            udp_socket->writeDatagram(response.data(), response.size(), datagram.senderAddress(), datagram.senderPort());
        }
    }
    //this stays active as long as server stays active
}

void server::newClientConnection()
{
    if (allClients.isEmpty()) {
        QTcpSocket* socket = srv1->nextPendingConnection();

        connect(socket, &QTcpSocket::readyRead, this, &server::socketReadReady); //called EACH TIME new data to read is available
        connect(socket, &QTcpSocket::stateChanged, this, &server::socketStateChanged); //called EACH TIME socket's state changes
        connect(socket, &QTcpSocket::disconnected, this, &server::socketDisconnected); //called when socket is disconnected

        qDebug() << "Player connected from " + socket->peerAddress().toString() + ":" + QString::number(socket->peerPort());
        allClients.push_back(socket);
    }
    else {
        qDebug() << "Player already connected.";
        //ÜBERARBEITEN DASS Z.B. ERSTE CONNECTION DER PLAYER UND REST CHAT IST
    }
}

//called from logic to confirm the game
void server::sendStartGameSlot(quint8 startPlayer, quint8 groupNo)
{
    if (!allClients.isEmpty()) {
        QTcpSocket* socket = allClients.first();
        qDebug() << "Server sending response 0x02 with arguments: " << startPlayer << " and " << groupNo;
        QDataStream stream(socket);
        stream << static_cast<quint8>(0x02) << startPlayer << groupNo;
        socket->flush(); // ensure data is sent
    }
    else {
        qDebug() << "Either no player available or you're just here for other functionalities.";
    }
}

void server::stopServer()
{
    if (srv1 != nullptr && srv1->isListening()) {
        srv1->close();
        while(!allClients.empty()) {
            allClients.first()->disconnectFromHost();
        }
        qDebug() << "Server stopped.";
    }
}

void server::socketReadReady()
{
    QTcpSocket* socket = allClients.first();

    QDataStream stream (socket);
    quint8 receivedCmd;
    stream >> receivedCmd;

    if (receivedCmd==0x01) { //Verbindungsanfrage
        qDebug() << "Received 0x01 from player. Calling Logic.";
        emit responseConnectionRequest();
    }
    else if (receivedCmd==0x03) { //Antwort auf Spielbeginn
        quint8 groupNo;
        stream >> groupNo;
        qDebug() << "Received 0x03 from player of group " << groupNo << ". Calling Logic.";
        emit receivedStartGameConfirm(groupNo);
    }
    else if (protocol::cmdLen.contains(receivedCmd)) { //beliebieges Spielkommando
        QByteArray fullCmd(protocol::cmdLen[receivedCmd] + 1, 0); //length array + 1 because protocol length only specifies #arguments
        fullCmd[0] = receivedCmd;

        quint8 tmp;
        for (quint8 i=1; i<=protocol::cmdLen[receivedCmd]; i++) {
            stream >> tmp; //each byte written seperately on array
            fullCmd[i] = tmp;
        }

        qDebug() << "Received command " << [fullCmd]() -> QString {
            QStringList elements;
            for (quint8 arg : fullCmd) {
                elements.append(QString("0x%1").arg(arg, 2, 16, QChar('0')));
            }
            return "[" + elements.join(", ") + "]";
        }() << ". Calling logic based on cmd.";

        emitAnything(fullCmd);
    }
    else {
        qDebug() << "Unknown command received from player: " << receivedCmd << ".";
    }
}


void server::socketDisconnected()
{
    QTcpSocket* client = qobject_cast<QTcpSocket*>(QObject::sender()); //multiple clients available, this line reads out the correct one
    qDebug() << "Socket disconnected from " + client->peerAddress().toString() + ":" + QString::number(client->peerPort());
    emit clientDisconnected();
    allClients.removeOne(client);
    allClients.shrink_to_fit();
}


void server::sendAnything(QByteArray arr)
{
    if (allClients.isEmpty()) {
        qDebug() << "no clients to send to";
        return;
    }

    QDataStream stream(allClients.first());
    for (quint8 value : arr) {
        qDebug() << "sendAnything() sent this from server: " << value;
        stream << value;
    }
    allClients.first()->flush(); //ensure data is sent
    qDebug() << "sendAnything() has sent the complete array from server.";
}


void server::socketStateChanged(QAbstractSocket::SocketState state)
{
    QTcpSocket* client = qobject_cast<QTcpSocket*>(QObject::sender()); //multiple clients available, this line reads out the correct one

    QString desc;
    switch (state) {
    case QAbstractSocket::UnconnectedState: desc = "Unconnected"; break;
    case QAbstractSocket::HostLookupState: desc = "Host Lookup"; break;
    case QAbstractSocket::ConnectingState: desc = "Connecting"; break;
    case QAbstractSocket::ConnectedState: desc = "Connected"; break;
    case QAbstractSocket::BoundState: desc = "Bound"; break;
    case QAbstractSocket::ListeningState: desc = "Listening"; break;
    case QAbstractSocket::ClosingState: desc = "Closing"; break;
    default: desc = "Unknown State"; break;
    }

    qDebug() << "Socket state changed (" + client->peerAddress().toString() + ":" + QString::number(client->peerPort()) + "): " + desc;
}
