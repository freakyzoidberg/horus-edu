#ifndef COMMPACKET_H
#define COMMPACKET_H

#include <QByteArray>
#include <QDebug>

#include "Defines.h"

/*!
 * After authentification, each packets are transmited inside this container
 */
class CommPacket
{
public:
    enum                pType { UNDEFINED, ERROR, INIT, ALIVE, LOGIN, FILE, CONFIG, MODULE, __LAST__ };

    CommPacket(pType _type);
    CommPacket(QByteArray&);

    pType               packetType;

    const QByteArray    getPacket();

protected:
    void                read(QByteArray&);
    void                write(QByteArray&);
};

// DEBUG
QDebug operator<<(QDebug, CommPacket&);

#endif // COMMPACKET_H
