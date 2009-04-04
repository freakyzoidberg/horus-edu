#ifndef LOGINCONTAINER_H
#define LOGINCONTAINER_H

#include "Defines.h"

class CommunicationContainer
{
 public:

    char clientVersion[VERSION_SIZE];

    char login[LOGIN_SIZE];

    /*!
     * Type of authenfication
     * in the future we may want to add the ssl certificate for auth. or something else
     */
    enum authType{HASH_MD5};
    uint  sizeCont;
    void* content;
};

#endif // LOGINCONTAINER_H
