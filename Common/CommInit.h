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
    QByteArray      getPacket();

    quint8          protoVersion;
    QByteArray      fromName;
};

QDebug operator<<(QDebug, CommInit&);

#endif // COMMINIT_H
