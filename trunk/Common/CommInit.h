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
    CommInit();
    CommInit(quint8 _protoVersion, const char* fromName);

    quint8          protoVersion;
    CommMiniString  fromName;
};

QDataStream& operator<<(QDataStream&, CommInit&);
QDataStream& operator>>(QDataStream&, CommInit&);

QDebug operator<<(QDebug, CommInit&);

#endif // COMMINIT_H
