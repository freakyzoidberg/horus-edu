#include "FileTransfertServer.h"
#include "FileServer.h"
#include "FileNetworkPlugin.h"
#include "../../../Common/DataImplementations/FileDataBase/FileDataBase.h"
#include "../../../Common/UserData.h"
#include <QTime>

QList<FileTransfertServer*>	FileTransfertServer::_transferts;
QList<FileTransfertServer*>	FileTransfertServer::_queue;

FileTransfertServer::FileTransfertServer(FileData* file, UserData* user, TransfertType type, FileNetworkPlugin* plugin) : FileTransfert(file, type)
{
	_user = user;
	_networkPlugin = plugin;
	moveToThread(&FileServer::instance()->thread);
    QMetaObject::invokeMethod(this, "init", Qt::QueuedConnection);
}

QByteArray FileTransfertServer::generateUniqueKey()
{
	QByteArray key;
//	qsrand(QTime::currentTime().msec());

	bool found;
	do
	{
		for (int i = 0; i < FILE_TRANSFERT_KEY_SIZE; i++)
			key[i] = qrand();

		found = false;
		foreach (FileTransfert* t, _transferts)
			if (t->key() == key)
			{
				found = true;
				break;
			}
	}
	while (found);
	return key;
}

void FileTransfertServer::init()
{
	_timer = new QTimer(this);
	connect(_timer, SIGNAL(timeout()), this, SLOT(deleteLater()));
	_timer->start(FILE_TRANSFERT_WAIT_TIME * 1000);
	_queue.append(this);
	checkQueue();
}

void FileTransfertServer::checkQueue()
{
	//chech if the is a running transfert for this user
	foreach (FileTransfertServer* t, _transferts)
		if (t->_user == _user)
			return;

	//then allow a new one, generate a authorisation key and inform the client
	foreach (FileTransfertServer* t, _queue)
		if (t->_user == _user)
		{
			_queue.removeOne(t);
			t->_key = generateUniqueKey();
			t->_timer->start(FILE_TRANSFERT_WAIT_TIME * 1000);
			_networkPlugin->transfertCanStart(t);
			_transferts.append(t);
			return;
		}
}

void FileTransfertServer::start(QSslSocket* socket)
{
    _socket = socket;
    qDebug() << "FileTransfert::clientConnected";
	disconnect(_timer, SIGNAL(timeout()), 0, 0);
	connect(_socket, SIGNAL(disconnected()), this, SLOT(deleteLater()), Qt::QueuedConnection);
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
	qDebug() << "~FileTransfert()";
	emit finished();
	delete _timer;
	_queue.removeOne(this);
	_transferts.removeOne(this);

    if (_type == UPLOAD)
    {
		FileDataBase* fileData = (FileDataBase*)_fileData;
		fileData->_hash = _hash->result();
		fileData->_size = _file->size();
		qDebug() << "~FileTransfert() saving size and hash" << fileData->_size << fileData->_hash.toHex();
		fileData->save();
        delete _hash;
    }

//	if (_socket)
//		_socket->deleteLater();;
	if (_file)
		delete _file;
	if (_hash)
		delete _hash;
	checkQueue();
}

void FileTransfertServer::registerSocket(const QByteArray& key, QSslSocket* socket)
{
	foreach (FileTransfertServer* t, _transferts)
		if (t->key() == key)
			return t->start(socket);

	qDebug() << "FileTransfert::registerSocket Key not found. Connexion dropped.";
	delete socket;
}
