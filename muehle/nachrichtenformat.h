#ifndef NACHRICHTENFORMAT_H
#define NACHRICHTENFORMAT_H

#include <QMap>

namespace protocol {
inline QMap<quint8, quint8> cmdLen = {{0x01, 0x00}, {0x02, 0x02}, {0x03, 0x01},
                                      {0x10, 0x04}, {0x11, 0x04}, {0x12, 0x05},
                                      {0x13, 0x01}, {0x20, 0x02}, {0x21, 0x02}};
}

#endif // NACHRICHTENFORMAT_H
