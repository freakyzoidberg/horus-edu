#ifndef LOGINCONTAINER_H
#define LOGINCONTAINER_H

class CommunicationContainer
{
 public:
    char login[LOGIN_SIZE];
    enum authType{HASH_MD5};//Login with certificate or something else can be added
    void* content;
};

#define AuthHashMD5 char test[32]

#endif // LOGINCONTAINER_H
