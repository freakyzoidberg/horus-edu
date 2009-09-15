#include "FileTransfert.h"

#include <QTime>

#include "../../../Common/Defines.h"
//#include "../../../Common/FileData.h"
#include "../../../Common/DataImplementations/FileDataBase/FileDataBase.h"
#include "FileServer.h"

QHash<QByteArray,FileTransfert*> FileTransfert::_transferts;

FileTransfert::FileTransfert(FileData* file, TransfertType type)
{
    qDebug() << "FileTransfert()";

    moveToThread(&FileServer::instance()->thread);
    _type = type;
    _fileData = (FileDataBase*)(file);
    _file= 0;
    _socket = 0;
    _hash = 0;

    //TODO maybe change this value
    qsrand(QTime::currentTime().msec() * _fileData->id());
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

    // autodelete 1second for tests
    _timer->start(FILE_TRANSFERT_WAIT_TIME * 1000);
}

void FileTransfert::socketToFile()
{
    qDebug() << "FileTransfert::socketToFile";
    QByteArray buf = _socket->readAll();
    _hash->addData(buf);
    _file->write(buf);
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
        _file = _fileData->file();
        _file->open(QIODevice::ReadOnly);
        connect(_socket, SIGNAL(bytesWritten(qint64)), this, SLOT(fileToSocket(qint64)));
        fileToSocket(8192);
    }
    else if (_type == UPLOAD)
    {
        _file = _fileData->file();
        _hash = new QCryptographicHash(QCryptographicHash::Sha1);
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
    if (_type == UPLOAD)
    {
        _fileData->_hash = _hash->result();
        qDebug() << "~FileTransfert() saving hash" << _fileData->_hash.toHex();
        _fileData->setStatus(Data::SAVING);
        delete _hash;
    }
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
