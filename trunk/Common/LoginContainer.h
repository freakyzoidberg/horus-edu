#ifndef LOGINCONTAINER_H
#define LOGINCONTAINER_H

#include "Defines.h"

/*!
 * Response from the client to the server
 * after the first "ConnexionMessage" from the server
 */
class CommunicationContainer
{
 public:
    /*!
     * Send the version of the client if there is some change in the protocol in the future
     */
    char clientVersion[VERSION_SIZE];

    char login[LOGIN_SIZE];

    /*!
     * Type of authenfication
     * in the future we may want to add the ssl certificate for auth. or something else
     */
    enum authType{HASH_MD5};

    int  sizeCont;
    void* content;
};

#endif // LOGINCONTAINER_H
