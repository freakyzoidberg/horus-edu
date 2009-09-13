#include "FileTransfert.h"

#include <QTime>

#include "../../../Common/Defines.h"
#include "../../../Common/FileData.h"
#include "FileServer.h"

QHash<QByteArray,FileTransfert*> FileTransfert::_transferts;

FileTransfert::FileTransfert(FileData* file, TransfertType type)
{
    qDebug() << "FileTransfert()";

    moveToThread(&FileServer::instance()->thread);
    _type = type;
    _fileData = file;
    _file= 0;
    _socket = 0;

    //TODO maybe change this value
    qsrand(QTime::currentTime().msec());
    for (int i = 0; i < FILE_TRANSFERT_KEY_SIZE; i++)
        _key[i] = qrand();

    QMetaObject::invokeMethod(this, "init", Qt::QueuedConnection);
}

void FileTransfert::init()
{
    qDebug() << "FileTransfert::init()";

    _transferts.insert(_key, this);
    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(deleteLater()));

//    _file->setParent(this);
    // 1second for tests
    _timer->start(FILE_TRANSFERT_WAIT_TIME * 1000);
}

void FileTransfert::socketToFile()
{
    qDebug() << "FileTransfert::socketToFile";
    _file->write(_socket->readAll());
}

void FileTransfert::fileToSocket(qint64)
{
    qDebug() << "FileTransfert::fileToSocket";
    _socket->write(_file->read(8192));
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
    if (_type == DOWNLOAD)
    {
        _file = _fileData->device();
        _file->open(QIODevice::ReadOnly);
        connect(_socket, SIGNAL(bytesWritten(qint64)), this, SLOT(fileToSocket(qint64)));
        fileToSocket(8192);
    }
    else if (_type == UPLOAD)
    {
        _file = _fileData->device();
        _file->open(QIODevice::WriteOnly | QIODevice::Truncate);
        connect(_socket, SIGNAL(readyRead()), this, SLOT(socketToFile()));
    }
    else
        _socket->disconnectFromHost();
}

FileTransfert::~FileTransfert()
{
    delete _timer;
//    if (_socket)
//        delete _socket;
    if (_file)
        delete _file;
    _transferts.remove(_key);
    qDebug() << "~FileTransfert()";
}

void FileTransfert::registerSocket(const QByteArray& key, QSslSocket* socket)
{
    FileTransfert* trans = _transferts.value(key);
    if ( ! trans)
    {
        qDebug() << "FileTransfert::registerSocket Key not found. Connexion dropped.";
        delete socket;
        //deleteLater();
        return;
    }

    trans->clientConnected(socket);
}
