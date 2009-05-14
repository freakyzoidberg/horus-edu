#ifndef FILESERVER_H
#define FILESERVER_H

#include <QTcpServer>

#include "FileTransfert.h"

class FileServer : public QTcpServer
{
  Q_OBJECT
public:
    FileServer(QObject* parent);

protected:
    void incomingConnection (int socket);


private:
    static QHash<QByteArray,FileTransfert*> map;
};

#endif // FILESERVER_H
