#ifndef COMMINIT_H
#define COMMINIT_H

#include "CommPacket.h"

/*!
 * First Message after connexion
 * From Server to the Client
 */
class CommInit : public CommPacket
{
public:
    CommInit(quint8 _protoVersion, const char* fromName);
    CommInit(QByteArray&);

    const QByteArray getPacket();

    quint8          protoVersion;
    QByteArray      fromName;

private:
    void                read(QByteArray&);
    void                write(QByteArray&);
};

QDebug operator<<(QDebug, CommInit&);

#endif // COMMINIT_H
