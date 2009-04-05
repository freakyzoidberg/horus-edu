#ifndef COMMINIT_H
#define COMMINIT_H

#include <QDataStream>

#include "Defines.h"

/*!
 * First Message after connexion
 * From Server to the Client
 * After, the client answer with a "LoginContainer" class
 */
class CommInit
{
public:
    //char serverName   []             = "Horus Server";
    char       serverVersion[VERSION_SIZE];
};

QDataStream& operator<<(QDataStream& ds, CommInit& lc);
QDataStream& operator>>(QDataStream& ds, CommInit& lc);

#endif // COMMINIT_H
