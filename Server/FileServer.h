#ifndef FILESERVER_H
#define FILESERVER_H

#include <QTcpServer>

//! a QTcpServer, to wait for file transfert connexions
class FileServer : public QTcpServer
{
  Q_OBJECT
public:
    FileServer();

protected:
    //! when a new connexion is openned
    void incomingConnection (int socket);
};

#endif // FILESERVER_H
