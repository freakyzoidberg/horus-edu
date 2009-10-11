#include "FileTransfertServer.h"
#include "FileServer.h"
#include "../../../Common/DataImplementations/FileDataBase/FileDataBase.h"
#include <QTime>

FileTransfertServer::FileTransfertServer(FileData* file, TransfertType type) : FileTransfert(file, type)
{
    moveToThread(&FileServer::instance()->thread);

    //TODO maybe change this value
    qsrand(QTime::currentTime().msec() * _fileData->id());
    for (int i = 0; i < FILE_TRANSFERT_KEY_SIZE; i++)
        _key[i] = qrand();

    QMetaObject::invokeMethod(this, "init", Qt::QueuedConnection);
}

void FileTransfertServer::init()
{
    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(deleteLater()));

    // autodelete 1second for tests
    _timer->start(FILE_TRANSFERT_WAIT_TIME * 1000);
}

//const QByteArray& FileTransfert::key() const
//{
//    return _key;
//}

void FileTransfertServer::clientConnected(QSslSocket* socket)
{
    _socket = socket;
    qDebug() << "FileTransfert::clientConnected";
    disconnect(_timer, SIGNAL(timeout()), 0, 0);
	connect(_socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::QueuedConnection);
    if (_type == DOWNLOAD)
    {
        _file = _fileData->file();
        _file->open(QIODevice::ReadOnly);
		connect(_socket, SIGNAL(bytesWritten(qint64)), this, SLOT(fileToSocket(qint64)), Qt::QueuedConnection);
		fileToSocket(0);
    }
    else if (_type == UPLOAD)
    {
        _file = _fileData->file();
        _hash = new QCryptographicHash(QCryptographicHash::Sha1);
        _file->open(QIODevice::WriteOnly | QIODevice::Truncate);
		connect(_socket, SIGNAL(readyRead()), this, SLOT(socketToFile()), Qt::QueuedConnection);
    }
    else
        _socket->disconnectFromHost();
}

FileTransfertServer::~FileTransfertServer()
{
    delete _timer;
    if (_type == UPLOAD)
    {
		FileDataBase* fileData = (FileDataBase*)_fileData;
		fileData->_hash = _hash->result();
		fileData->_size = _file->size();
		qDebug() << "~FileTransfert() saving size and hash" << fileData->_size << fileData->_hash.toHex();
		fileData->save();
        delete _hash;
    }
}

void FileTransfertServer::registerSocket(const QByteArray& key, QSslSocket* socket)
{
	foreach (FileTransfert* trans, (QList<FileTransfert*>&)FileTransfertList::list())
		if (trans->key() == key)
			return ((FileTransfertServer*)trans)->clientConnected(socket);

	qDebug() << "FileTransfert::registerSocket Key not found. Connexion dropped.";
	delete socket;
}
