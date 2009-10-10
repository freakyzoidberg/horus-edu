#include "FileTransfertClient.h"
#include "../../../Common/FileData.h"

#include <QSettings>
#include <QDir>
#include <QBoxLayout>
#include <QLabel>
#include <QProgressBar>

FileTransfertClient::FileTransfertClient(FileData* file, TransfertType type, const QByteArray& key) : FileTransfert(file, type)
{
	moveToThread(file->thread());
	_key = key;
	_file = _fileData->file();
	connectToServer();
	connect(_socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::QueuedConnection);

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

QWidget* FileTransfertClient::progressBar()
{
	QWidget* widget = new QWidget;
	QBoxLayout* layout = new QBoxLayout(QBoxLayout::LeftToRight, widget);
	widget->setLayout(layout);

	layout->addWidget(new QLabel(QVariant(_fileData->id()).toString(), widget));
	layout->addWidget(new QLabel(_fileData->name(), widget));
	QProgressBar* bar = new QProgressBar;
	bar->setRange(0, _fileData->size());
	bar->setValue(_progress);
	connect(this, SIGNAL(progressChange(int)), bar, SLOT(setValue(int)));
	layout->addWidget(bar);
	layout->addWidget(new QLabel(QVariant(_fileData->size()).toString(), widget));
	layout->addWidget(new QLabel(QVariant(_progress).toString(), widget));
	return widget;
}
