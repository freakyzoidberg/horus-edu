#ifndef CONNEXIONMESSAGE_H
#define CONNEXIONMESSAGE_H

#include "Defines.h"

/*!
 * First Message after connexion
 * From Server to the Client
 * After, the client answer with a "LoginContainer" class
 */
class ConnexionMessage
{
    //static char serverName   []             = "Horus Server";
    char       serverVersion[VERSION_SIZE];
}

#endif // CONNEXIONMESSAGE_H
