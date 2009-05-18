#include "FileTransfert.h"

#include "ThreadFiles.h"
#include <QTimer>

FileTransfert::FileTransfert(QFile* _file)
{
    file = _file;
    moveToThread(ThreadFiles::instance());
//    qDebug() << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    QTimer::singleShot(2000, this, SLOT(endOfListening()));
}

void FileTransfert::endOfListening()
{
    qDebug() << "ca va";
    sleep(2);
    qDebug() << "finir";
}

const QByteArray& FileTransfert::getKey()
{
    return key;
}

void FileTransfert::clientConnected(QSslSocket* _socket)
{
    socket = _socket;
}
