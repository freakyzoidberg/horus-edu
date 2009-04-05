#ifndef REQUEST_H
#define REQUEST_H

#include <QRunnable>

#include "ClientSocket.h"

class Request : public QRunnable
{
public:
    Request(ClientSocket* cs);
    void run();

private:
    ClientSocket* client;
};

#endif // REQUEST_H
