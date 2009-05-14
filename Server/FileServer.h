#ifndef FILESERVER_H
#define FILESERVER_H

#include <QTcpServer>

#include "FileTransfert.h"

//! a QTcpServer, to wait for file transfert connexions
class FileServer : public QTcpServer
{
  Q_OBJECT
public:
    FileServer(QObject* parent);

protected:
    //! when a new connexion is openned
    void incomingConnection (int socket);

private:
    //! hashtable of the current transferts (already started or not)
    static QHash<QByteArray,FileTransfert*> map;
};

#endif // FILESERVER_H
