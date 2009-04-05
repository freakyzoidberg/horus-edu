#ifndef COMMINIT_H
#define COMMINIT_H

#include <QDataStream>

#include "CommMiniString.h"

/*!
 * First Message after connexion
 * From Server to the Client
 * After, the client answer with a "LoginContainer" class
 */
class CommInit
{
public:
    CommInit(CommMiniString serverVersion = "1");

    CommMiniString  serverName;
    CommMiniString  serverVersion;
};

QDataStream& operator<<(QDataStream&, CommInit&);
QDataStream& operator>>(QDataStream&, CommInit&);

#endif // COMMINIT_H
