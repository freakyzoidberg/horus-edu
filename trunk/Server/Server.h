#ifndef FORTUNESERVER_H
#define FORTUNESERVER_H

#include <QTcpServer>

#include "../Common/Defines.h"
#include "ClientSocket.h"
#include "Settings.h"

//! The base server. this object just listen to a port and create ClientSocket for each connexion
class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(QObject *parent = 0);

protected:
    //! called when there is an incomming connexion. Virtual method of QTcpServer.
    void incomingConnection(int socketDescriptor);
};

#endif
