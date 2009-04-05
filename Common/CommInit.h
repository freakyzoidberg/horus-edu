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

    quint8          serverProtoVersion;
    CommMiniString  serverName;
    //Maybe add suported authType by the server
};

QDataStream& operator<<(QDataStream&, CommInit&);
QDataStream& operator>>(QDataStream&, CommInit&);

#endif // COMMINIT_H
