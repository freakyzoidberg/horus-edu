#ifndef FILETRANSFERT_H
#define FILETRANSFERT_H

#include <QObject>
#include <QSslSocket>
#include <QFile>

//! the object for each file transfert
class FileTransfert : public QObject
{
public:
    FileTransfert(int socket, QObject* parent=0);

private:
    //! socket to the client
    QSslSocket socket;
    //! opened local file
    QFile      file;
};

#endif // FILETRANSFERT_H
