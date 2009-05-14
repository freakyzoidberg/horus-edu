#ifndef FILETRANSFERT_H
#define FILETRANSFERT_H

#include <QObject>
#include <QSslSocket>
#include <QFile>

class FileTransfert : public QObject
{
public:
    FileTransfert(int socket, QObject* parent=0);

private:
    QSslSocket socket;
    QFile      file;
};

#endif // FILETRANSFERT_H
