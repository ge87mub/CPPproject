#ifndef CLIENT_H
#define CLIENT_H

#include "networkmanager.h"
#include <QTcpSocket>
#include <QUdpSocket>
#include <QString>
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
#include <QtTypes>
#else
#include <QtGlobal>
#endif
#include <QObject>
#include <QByteArray>

class client : public networkManager
{
    Q_OBJECT
private:
    bool connectedToHost = false;
    QTcpSocket* socket = nullptr;
    QUdpSocket* udp_socket = nullptr;
    void handleSocketError();

public slots:
    void socketConnected();
    void socketDisconnected();
    void socketReadyRead();
    void on_connectButton_clicked(const QString& host, quint16 port);
    void confirmGameSlot(quint8 groupNo);
    void udpBroadcast(quint16 port);
    void handleUdpResponse();
    void stopClient();

signals:
    void startGameSignal(quint8 startPlayer, quint8 groupNo); // for logic to notify a start game cmd was received
    void socketErrorOccurred(QString error); // for gui to get a error msg if connection was not able
    void clientConnected();
    void serverDisconnected();

public:
    explicit client(QObject *parent = nullptr);
    virtual void sendAnything(QByteArray arr) override;
};

#endif // CLIENT_H
