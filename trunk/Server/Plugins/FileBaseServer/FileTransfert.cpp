#include "FileTransfert.h"

#include <QTime>

#include "../../../Common/Defines.h"
#include "../../../Common/FileData.h"

QHash<QByteArray,FileTransfert*> FileTransfert::_transferts;

FileTransfert::FileTransfert(FileData* file)
{
    qDebug() << "FileTransfert(...)";
    _file = file->localFile();
    _file->setParent(this);
    _timer = new QTimer(this);
    _socket = 0;

    //TODO maybe change this value
    qsrand(QTime::currentTime().msec());
    for (int i = 0; i < FILE_TRANSFERT_KEY_SIZE; i++)
        _key[i] = qrand();

//    moveToThread(ThreadFiles::instance());

    connect(this, SIGNAL(start()), this, SLOT(startSlot()), Qt::QueuedConnection);
    emit start();
}

void FileTransfert::startSlot()
{
    disconnect(this, SLOT(startSlot()));
    connect(_timer, SIGNAL(timeout()), this, SLOT(deleteLater()));
    _transferts.insert(_key, this);
    // 1second for tests
    _timer->start(FILE_TRANSFERT_WAIT_TIME * 1000);
}

void FileTransfert::socketToFile()
{
    qDebug() << "FileTransfert::socketToFile";
    _file->write(_socket->readAll());
}

void FileTransfert::fileToSocket(qint64 len)
{
    qDebug() << "FileTransfert::fileToSocket";
    _socket->write(_file->read(len));
    if (_file->atEnd())
    {
        _socket->flush();
        _socket->close();
    }
}

const QByteArray& FileTransfert::key() const
{
    return _key;
}

void FileTransfert::clientConnected(QSslSocket* socket)
{
    _socket = socket;
    qDebug() << "FileTransfert::clientConnected";
    disconnect(_timer, SIGNAL(timeout()), 0, 0);
    connect(_socket, SIGNAL(disconnected()), this, SLOT(deleteLater()));
    if (_file->openMode() & QFile::WriteOnly)
        connect(_socket, SIGNAL(readyRead()), this, SLOT(socketToFile()));
    if (_file->openMode() & QFile::ReadOnly)
    {
        connect(_socket, SIGNAL(bytesWritten(qint64)), this, SLOT(fileToSocket(qint64)));
        fileToSocket(8192);
    }
}

FileTransfert::~FileTransfert()
{
    delete _timer;
    delete _file;
    _transferts.remove(_key);
    qDebug() << "~FileTransfert()";
}

void FileTransfert::registerSocket(const QByteArray& key, QSslSocket* socket)
{
    FileTransfert* trans = _transferts.value(key);
    if ( ! trans)
    {
        delete socket;
        return;
    }

    trans->clientConnected(socket);
}
