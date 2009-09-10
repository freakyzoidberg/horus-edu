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
     * __LAST__ is used to know if a value is valid. a valid value is always inferior to __LAST__. __LAST__ is never used as a value
     */
    enum                Type { UNDEFINED, ERROR, INIT, ALIVE, LOGIN, DATA, PLUGIN, __LAST__ };

    //! constuctor to send a new packet
    CommPacket(Type _type);
    //! constructor when receiving a packet (just call a read())
    CommPacket(const QByteArray&);
    //! create the concated packet
    const QByteArray    getPacket() const;

    static void debugPacket(QDebug, const QByteArray&);

    //! type of the packet
    Type                packetType;

protected:
    void                read(const QByteArray&);
    void                write(QByteArray&) const;
    inline int          lenParent() const { return 1; }
};

QDebug operator<<(QDebug, const CommPacket&);

#endif // COMMPACKET_H
