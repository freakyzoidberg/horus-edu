#ifndef COMMPACKET_H
#define COMMPACKET_H

#include <QDataStream>
#include <QObject>
#include <QDebug>

#include "Defines.h"
#include "CommMiniString.h"

/*!
 * After authentification, each packets are transmited inside this container
 */
class CommPacket
{
  Q_ENUMS(type)
public:
    enum                type { UNKNOW, ERROR, INIT, ALIVE, LOGIN, FILE, CONFIG, MODULE };

    const char*         packetName();

    static CommPacket*  readNextPacket(QDataStream&);

//protected:
    CommPacket(type _type = UNKNOW);

//private:
    type                packetType;

    static const quint8 typeNumber;
    static const char*  typeNames[];
};

QDataStream& operator<<(QDataStream&, CommPacket&);
QDataStream& operator>>(QDataStream&, CommPacket&);

QDebug operator<<(QDebug, CommPacket&);

#endif // COMMPACKET_H
