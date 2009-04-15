#ifndef COMMPACKET_H
#define COMMPACKET_H

#include <QDataStream>
#include <QDebug>
#include <QMetaEnum>

#include "Defines.h"

/*!
 * After authentification, each packets are transmited inside this container
 */
class CommPacket
{
public:
    enum                type { UNKNOW, ERROR, INIT, ALIVE, LOGIN, FILE, CONFIG, MODULE };

    CommPacket(type _type);
    CommPacket(QByteArray&);

    quint8               packetType;

    const QByteArray   getPacket();

public:
    static const quint8 typeNumber;
    static const char*  typeNames[];
};

QDebug operator<<(QDebug, CommPacket&);

#endif // COMMPACKET_H
