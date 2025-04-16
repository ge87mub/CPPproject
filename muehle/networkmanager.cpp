#include "networkmanager.h"
#include <QDebug>
#include "nachrichtenformat.h"

networkManager::networkManager(QObject *parent)
    : QObject(parent)
{}

//this method emits signals used globally across client/server based on who calls it
void networkManager::emitAnything(QByteArray arr)
{
    switch(static_cast<quint8>(arr[0])) {
        case 0x10:
            emit setSignal(static_cast<Orientation>(static_cast<quint8>(arr[1])),
                           static_cast<Square>(static_cast<quint8>(arr[2])),
                           static_cast<quint8>(arr[3]),
                           static_cast<bool>(arr[4]));
            qDebug() << "emitAnything() in networkManager emitted setSignal.";
            break;
        case 0x11:
            emit moveSignal(static_cast<Orientation>(static_cast<quint8>(arr[1])),
                            static_cast<Square>(static_cast<quint8>(arr[2])),
                            static_cast<Orientation>(static_cast<quint8>(arr[3])),
                            static_cast<bool>(arr[4]));
            qDebug() << "emitAnything() in networkManager emitted moveSignal.";
            break;
        case 0x12:
            emit jumpSignal(static_cast<Orientation>(static_cast<quint8>(arr[1])),
                            static_cast<Square>(static_cast<quint8>(arr[2])),
                            static_cast<Orientation>(static_cast<quint8>(arr[3])),
                            static_cast<Square>(static_cast<quint8>(arr[4])),
                            static_cast<bool>(arr[5]));
            qDebug() << "emitAnything() in networkManager emitted jumpSignal.";
            break;
        case 0x13:
            emit confirmSetMoveJumpSignal(static_cast<MoveStatus>(static_cast<quint8>(arr[1])));
            qDebug() << "emitAnything() in networkManager emitted confirmSetMoveJumpSignal.";
            break;
        case 0x20:
            emit removeSignal(static_cast<Orientation>(static_cast<quint8>(arr[1])),
                              static_cast<Square>(static_cast<quint8>(arr[2])));
            qDebug() << "emitAnything() in networkManager emitted removeSignal.";
            break;
        case 0x21:
            emit confirmRemoveSignal(static_cast<RemoveStatus>(static_cast<quint8>(arr[1])),
                                     static_cast<quint8>(arr[2]));
            qDebug() << "emitAnything() in networkManager emitted confirmRemoveSignal.";
            break;
        default:
            break;
    }
}

void networkManager::sendSetSlot(Orientation newH, Square newQ, quint8 remaining, bool muehle)
{
    quint8 cmd = 0x10;
    QByteArray sendArr(protocol::cmdLen[cmd] + 1, 0);

    sendArr[0] = cmd;
    sendArr[1] = static_cast<quint8>(newH);
    sendArr[2] = static_cast<quint8>(newQ);
    sendArr[3] = remaining;
    sendArr[4] = static_cast<quint8>(muehle);

    sendAnything(sendArr);
}

void networkManager::sendMoveSlot(Orientation oldH, Square oldQ, Orientation newH, bool muehle)
{
    quint8 cmd = 0x11;
    QByteArray sendArr(protocol::cmdLen[cmd] + 1, 0);

    sendArr[0] = cmd;
    sendArr[1] = static_cast<quint8>(oldH);
    sendArr[2] = static_cast<quint8>(oldQ);
    sendArr[3] = static_cast<quint8>(newH);
    sendArr[4] = static_cast<quint8>(muehle);

    sendAnything(sendArr);
}

void networkManager::sendJumpSlot(Orientation oldH, Square oldQ, Orientation newH, Square newQ, bool muehle)
{
    quint8 cmd = 0x12;
    QByteArray sendArr(protocol::cmdLen[cmd] + 1, 0);

    sendArr[0] = cmd;
    sendArr[1] = static_cast<quint8>(oldH);
    sendArr[2] = static_cast<quint8>(oldQ);
    sendArr[3] = static_cast<quint8>(newH);
    sendArr[4] = static_cast<quint8>(newQ);
    sendArr[5] = static_cast<quint8>(muehle);

    sendAnything(sendArr);
}

void networkManager::sendRemoveSlot(Orientation oldH, Square oldQ)
{
    quint8 cmd = 0x20;
    QByteArray sendArr(protocol::cmdLen[cmd] + 1, 0);

    sendArr[0] = cmd;
    sendArr[1] = static_cast<quint8>(oldH);
    sendArr[2] = static_cast<quint8>(oldQ);

    sendAnything(sendArr);
}

void networkManager::confirmSetMoveJumpSlot(MoveStatus statusCode)
{
    quint8 cmd = 0x13;
    QByteArray sendArr(protocol::cmdLen[cmd] + 1, 0);

    sendArr[0] = cmd;
    sendArr[1] = static_cast<quint8>(statusCode);

    sendAnything(sendArr);
}

void networkManager::confirmRemoveSlot(RemoveStatus statusCode, quint8 count)
{
    quint8 cmd = 0x21;
    QByteArray sendArr(protocol::cmdLen[cmd] + 1, 0);

    sendArr[0] = cmd;
    sendArr[1] = static_cast<quint8>(statusCode);
    sendArr[2] = count;

    sendAnything(sendArr);
}
