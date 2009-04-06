#ifndef COMMINIT_H
#define COMMINIT_H

#include <QDataStream>

#include "Defines.h"
#include "CommMiniString.h"

/*!
 * First Message after connexion
 * From Server to the Client
 * After, the client answer with a "LoginContainer" class
 */
class CommInit
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
