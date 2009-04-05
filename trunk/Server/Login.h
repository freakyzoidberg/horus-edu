#ifndef LOGIN_H
#define LOGIN_H

#include <QRunnable>

#include "ClientSocket.h"

class Login : public QRunnable
{
public:
    Login(ClientSocket* cs);
    void run();

private:
    ClientSocket* client;
};

#endif // LOGIN_H
