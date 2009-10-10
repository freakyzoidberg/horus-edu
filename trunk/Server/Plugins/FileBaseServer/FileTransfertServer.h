#ifndef FILETRANSFERTSERVER_H
#define FILETRANSFERTSERVER_H

#include "../../../Common/DataImplementations/FileDataBase/FileTransfert.h"

class FileTransfertServer : public FileTransfert
{
  Q_OBJECT
public:
	FileTransfertServer(FileData* file, TransfertType type);
	~FileTransfertServer();
    void clientConnected(QSslSocket* socket);

private:
    QTimer*             _timer;

private slots:
    void init();

public:
    static void registerSocket(const QByteArray& key, QSslSocket* socket);
};

#endif // FILETRANSFERTSERVER_H
