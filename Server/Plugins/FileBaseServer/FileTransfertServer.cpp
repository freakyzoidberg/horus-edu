/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
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
		_file.setFileName(_fileData->fileName());
		_file.open(QIODevice::ReadOnly);
		if ( ! _file.isOpen())
			qDebug() << "Cannot read file" << _file.fileName() << "Please check your configuration.";
		connect(_socket, SIGNAL(bytesWritten(qint64)), this, SLOT(fileToSocket(qint64)), Qt::QueuedConnection);
		fileToSocket(0);
    }
    else if (_type == UPLOAD)
    {
		_file.setFileName(_fileData->fileName());
        _hash = new QCryptographicHash(QCryptographicHash::Sha1);
		_file.open(QIODevice::WriteOnly | QIODevice::Truncate);
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
		fileData->_size = _file.size();
		qDebug() << "~FileTransfert() saving size and hash" << fileData->_size << fileData->_hash.toHex();
		fileData->save();
    }

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
