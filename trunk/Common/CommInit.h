#ifndef COMMINIT_H
#define COMMINIT_H

#include "CommPacket.h"

/*!
 * First Message after connexion
 * From Server to the Client
 */
//! Communication packet to initilize the connexion
class CommInit : public CommPacket
{
public:
    CommInit(quint8 _protoVersion, const char* fromName);
    CommInit(const QByteArray&);
    const QByteArray getPacket() const;

    //! protocol version
    quint8          protoVersion;
    //! name of the client for additional information (not used yet)
    QByteArray      fromName;

private:
    void                read(const QByteArray&);
    void                write(QByteArray&) const;
};

QDebug operator<<(QDebug, const CommInit&);

#endif // COMMINIT_H
