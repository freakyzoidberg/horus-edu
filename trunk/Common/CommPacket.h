#ifndef COMMPACKET_H
#define COMMPACKET_H

#include <QDataStream>
#include <QObject>
#include <QDebug>

#include "CommMiniString.h"

/*!
 * After authentification, each packets are transmited inside this container
 */
class CommPacket
{
  Q_ENUMS(pType)
public:
    enum                 pType { UNKNOW, ERROR, INIT, ALIVE, LOGIN, FILE, CONFIG, MODULE };

    pType               getPacketType();
    const char*         getPacketName();

    static CommPacket*  readNextPacket(QDataStream&);

//protected:
    CommPacket(pType _type = UNKNOW);

//private:
    pType               packetType;

    static const quint8 typeNumber;
    static const char*  typeNames[];
};

QDataStream& operator<<(QDataStream&, CommPacket&);
QDataStream& operator>>(QDataStream&, CommPacket&);

QDebug operator<<(QDebug, CommPacket&);

#endif // COMMPACKET_H
