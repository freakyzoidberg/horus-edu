#ifndef FORTUNESERVER_H
#define FORTUNESERVER_H

#include <QTcpServer>

#include "../Common/Defines.h"
#include "ClientSocket.h"
#include "Settings.h"

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(QObject *parent = 0);

protected:
    void incomingConnection(int socketDescriptor);
    void check();
};

#endif
