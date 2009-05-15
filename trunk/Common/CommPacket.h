#ifndef COMMPACKET_H
#define COMMPACKET_H

#include <QByteArray>
#include <QDebug>

#include "Defines.h"

/*!
 * After authentification, each packets are transmited inside this container
 */
//! Parent Communication packet. Just define the type of the transmited packet
class CommPacket
{
public:
    //! type of the packet
    /*!
     * UNDEFINED is used when the type is not set yet, and for invalid value
     * __LAST__ is usde to know if a value is valid. a valid value is always inferior to __LAST__. __LAST__ is never used as a value
     */
    enum                Type { UNDEFINED, ERROR, INIT, ALIVE, LOGIN, FILE, SETTINGS, PLUGIN, __LAST__ };

    //! constuctor to send a new packet
    CommPacket(Type _type);
    //! constructor when receiving a packet (just call a read())
    CommPacket(QByteArray&);
    //! create the concated packet
    const QByteArray    getPacket();

    //! type of the packet
    Type                packetType;

protected:
    void                read(QByteArray&);
    void                write(QByteArray&);
};

QDebug operator<<(QDebug, const CommPacket&);

#endif // COMMPACKET_H
