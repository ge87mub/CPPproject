#ifndef SERVER_H
#define SERVER_H

#include "networkmanager.h"
#include <QTcpServer>
#include <QVector>
#include <QTcpSocket>
#include <QUdpSocket>
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
#include <QtTypes>
#else
#include <QtGlobal>
#endif
#include <QAbstractSocket>
#include <QString>
#include <QObject>
#include <QByteArray>

class server : public networkManager
{
    Q_OBJECT
private:
    QTcpServer* srv1 = nullptr;
    QUdpSocket* udp_socket = nullptr;
    QVector<QTcpSocket*> allClients;


public slots:
    void startServer(quint16 port);
    void newClientConnection();
    void socketDisconnected();
    void socketReadReady();
    void socketStateChanged(QAbstractSocket::SocketState state);
    void sendStartGameSlot(quint8 startPlayer, quint8 groupNo);
    void handleServerError();
    void stopServer();
    void handleUdpInquiry();

signals:
    void responseConnectionRequest();
    void receivedStartGameConfirm(quint8 groupNo);
    void serverErrorOccurred(QString error);
    void serverStarted();
    void clientDisconnected();

public:
    explicit server(QObject *parent = nullptr);
    virtual void sendAnything(QByteArray arr) override;

};

#endif // SERVER_H
