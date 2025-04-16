#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QByteArray>
#include "orientation.h"
#include "square.h"
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
#include <QtTypes>
#else
#include <QtGlobal>
#endif
#include "movestatus.h"
#include "removestatus.h"

class networkManager : public QObject
{
    Q_OBJECT
public:
    explicit networkManager(QObject *parent = nullptr);
    virtual void sendAnything(QByteArray arr) = 0;
    void emitAnything(QByteArray arr);

signals:
    void setSignal(Orientation newH, Square newQ, quint8 remaining, bool muehle);
    void moveSignal(Orientation oldH, Square oldQ, Orientation newH, bool muehle);
    void jumpSignal(Orientation oldH, Square oldQ, Orientation newH, Square newQ, bool muehle);
    void removeSignal(Orientation oldH, Square oldQ);
    void confirmSetMoveJumpSignal(MoveStatus statusCode);
    void confirmRemoveSignal(RemoveStatus statusCode, quint8 count);

public slots:
    void sendSetSlot(Orientation newH, Square newQ, quint8 remaining, bool muehle);
    void sendMoveSlot(Orientation oldH, Square oldQ, Orientation newH, bool muehle);
    void sendJumpSlot(Orientation oldH, Square oldQ, Orientation newH, Square newQ, bool muehle);
    void sendRemoveSlot(Orientation oldH, Square oldQ);
    void confirmSetMoveJumpSlot(MoveStatus statusCode);
    void confirmRemoveSlot(RemoveStatus statusCode, quint8 count);
};

#endif // NETWORKMANAGER_H
