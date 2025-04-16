#include "client.h"
#include <QDebug>
#include <QDataStream>
#include "nachrichtenformat.h"
#include <QStringList>
#include <QNetworkDatagram>

client::client(QObject *parent)
    : networkManager(parent)
{}

//NEW slot to activate IF gui is clicked option udp discovery
void client::udpBroadcast(quint16 port) {
    udp_socket = new QUdpSocket(this);

    udp_socket->bind(QHostAddress::Any, port, QUdpSocket::ShareAddress); //listens to any connection on given port, ShareAdress means "Allow other services to bind to the same address and port." (not secure)
    connect(udp_socket, &QUdpSocket::readyRead, this, &client::handleUdpResponse);

    QByteArray datagram = "TUM";
    udp_socket->writeDatagram(datagram.data(), datagram.size(), QHostAddress::Broadcast, port); //broadcast the datagram out to any ip adress on the specified port
    qDebug() << "Broadcasted datagram <TUM> to all listening servers.";
}

//NEW slot to receive incoming datagram from server
void client::handleUdpResponse() {
    QString pwd = "GROUP5";

    //switch to TCP if response is correct, 10 attemps should be enough
    for (quint8 i=10; i>0 && udp_socket->hasPendingDatagrams(); i--) {
        QNetworkDatagram datagram = udp_socket->receiveDatagram();
        if (pwd == QString::fromUtf8(datagram.data())) { //reassure correct server is connecting here
            qDebug() << "Server found! Switching to TCP...";
            on_connectButton_clicked(datagram.senderAddress().toString(), datagram.senderPort());
        }
    }

    udp_socket->disconnectFromHost();
}


//method is called with signal-slot from gui when connect button is clicked
void client::on_connectButton_clicked(const QString& host, quint16 port) {
    if (connectedToHost) {
        qDebug() << "This client is already connected!";
        return;
    }

    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::connected, this, &client::socketConnected); //called when connection is established, has to check whether possible (Verbindungsanfrage)
    connect(socket, &QTcpSocket::readyRead, this, &client::socketReadyRead); //called EACH TIME socket has data to read
    connect(socket, &QTcpSocket::disconnected, this, &client::socketDisconnected); //called when connection is disabled
    connect(socket, &QTcpSocket::errorOccurred, this, &client::handleSocketError);

    socket->connectToHost(host, port);
    qDebug() << "Connecting to server...";
}

void client::stopClient()
{
    if (!connectedToHost) {
        qDebug() << "This client is NOT connected!";
        return;
    }

    socket->disconnectFromHost();
    qDebug() << "Disconnected from server.";
    emit serverDisconnected();
    connectedToHost = false;
}

void client::socketConnected()
{
    qDebug() << "Socket connected to server.";

    QDataStream anfrage(socket);
    anfrage << static_cast<quint8>(0x01); //schicke Verbindungsanfrage 0x01
    socket->flush(); //ensure data is sent
}

void client::socketReadyRead()
{
    QDataStream stream(socket);
    quint8 receivedCmd;
    stream >> receivedCmd;

    if (receivedCmd==0x02) { //Antwort auf Verbindungsanfrage
        qDebug() << "Verbindungsanfrage confirmed, let's fucking go!";
        connectedToHost = true;
        emit clientConnected();

        quint8 startPlayer, groupNo;
        stream >> startPlayer;
        stream >> groupNo;

        qDebug() << "Received 0x02 with arguments: " << startPlayer << " and " << groupNo << ". Calling logic.";
        emit startGameSignal(startPlayer, groupNo);
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
        qDebug() << "Unknown command received from server: " << receivedCmd << ".";
    }
}

void client::socketDisconnected()
{
    qDebug() << "Sending request to disconnect from server.";
    emit serverDisconnected();
    connectedToHost = false;
}

void client::confirmGameSlot(quint8 groupNo) //Anwort auf Spielbeginnn, siehe Protokoll
{
    qDebug() << "Client sending confirm game with group " << groupNo << ".";
    QByteArray arr = QByteArray();
    arr.append(static_cast<quint8>(0x03));
    arr.append(groupNo);
    sendAnything(arr);
}

void client::sendAnything(QByteArray arr)
{
    if (!connectedToHost) {
        qDebug() << "not connected";
        return;
    }

    QDataStream stream(socket);
    for (quint8 value : arr) {
        qDebug() << "sendAnything() sent this from client: " << value;
        stream << value;
    }
    socket->flush(); //ensure data is sent
    qDebug() << "sendAnything() has sent the complete array from client.";
}

void client::handleSocketError()
{
    emit socketErrorOccurred(socket->errorString());
}
