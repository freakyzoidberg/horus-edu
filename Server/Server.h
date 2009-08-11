#ifndef SERVER_H 
#define SERVER_H

#include <QTcpServer>

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
