#include "FileTransfertClient.h"
#include "../../../Common/DataImplementations/FileDataBase/FileDataBase.h"

#include <QSettings>
#include <QDir>

FileTransfertClient::FileTransfertClient(FileData* file, TransfertType type, const QByteArray& key) : FileTransfert(file, type)
{
	moveToThread(file->thread());
	_key = key;
	_file = _fileData->file();
	_isFinished = false;
	_speed = 0;
	_lastProgress = 0;
	_startTime = QDateTime::currentDateTime().toTime_t();
	_isFinished = false;
	_speedTimer.setInterval(1000);
	_speedTimer.start();
	connect(&_speedTimer, SIGNAL(timeout()), this, SLOT(calcSpeed()));
	connectToServer();
	connect(_socket, SIGNAL(disconnected()), this, SLOT(finish()), Qt::QueuedConnection);

	if (_type == DOWNLOAD)
	{
		_file->open(QIODevice::WriteOnly | QIODevice::Truncate);
		connect(_socket, SIGNAL(readyRead()), this, SLOT(socketToFile()), Qt::QueuedConnection);
	}
	else
	{
		_file->open(QIODevice::ReadOnly);
		_hash = new QCryptographicHash(QCryptographicHash::Sha1);
		connect(_socket, SIGNAL(bytesWritten(qint64)), this, SLOT(fileToSocket(qint64)), Qt::QueuedConnection);
	}
}

void FileTransfertClient::connectToServer()
{
	qDebug() << "File::connectToServer()";

	_socket = new QSslSocket;
	_socket->setProtocol(QSsl::SslV3);
	_socket->setPeerVerifyMode(QSslSocket::VerifyNone);

	connect(_socket, SIGNAL(encrypted()), this, SLOT(connexionEncrypted()));

	QSettings settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);
	_socket->connectToHostEncrypted(settings.value("Network/Server", "localhost").toString(),
									settings.value("Network/PortTransfert", 42042).toInt());
}

void FileTransfertClient::connexionEncrypted()
{
	disconnect(_socket, SIGNAL(encrypted()), this, SLOT(connexionEncrypted()));
	_socket->write(_key);
	_socket->flush();
}

void FileTransfertClient::calcSpeed()
{
	_speed = _progress - _lastProgress;
	emit speedChange(_speed);

	_lastProgress = _progress;
}

void FileTransfertClient::finish()
{
	disconnect(this, SLOT(socketToFile()));
	disconnect(this, SLOT(fileToSocket(qint64)));
	disconnect(this, SLOT(calcSpeed()));
	_speedTimer.stop();

	((FileDataBase*)(_fileData))->_size = _file->size();
	uint duration = QDateTime::currentDateTime().toTime_t() - _startTime;
	if (duration)
		_speed = _fileData->size() / duration;
	else
		_speed = 0;


	emit finished();
	_isFinished = true;

//	if (_socket)
//		_socket->deleteLater();;
	if (_file)
		delete _file;
	if (_hash)
		delete _hash;
}