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
#include "NetworkManager.h"

#include <../Common/LocalSettings.h>
#include <QDir>
#include <QMetaObject>

#include "PluginManagerClient.h"
#include "CacheManager.h"
#include "UserCache.h"
#include "NetworkPlugin.h"
#include "../Common/CommInit.h"
#include "../Common/CommLogin.h"
#include "../Common/CommPlugin.h"
#include "../Common/CommPacket.h"
#include "../Common/CommData.h"
#include "../Common/CommError.h"

NetworkManager* NetworkManager::instance()
{
	static NetworkManager* _instance = 0;
	if ( ! _instance)
	{
		_instance = new NetworkManager;
		_instance->moveToThread(SecondaryThread::instance());
		qRegisterMetaType<UserData*>("UserData*");
	}
	return _instance;
}

QDebug operator<<(QDebug d, const NetworkManager::Status& s)
{
	static const char*  messages[] =
	{
		"DISCONNECTED",
		"CONNECTED",
		"ESTABLISHED",
		"LOGGED_IN"
	};
	return d << messages[ s ];
}

NetworkManager::NetworkManager()
{
	_status = DISCONNECTED;
	_nbrDatasForUpdate = 0;

	connect(this, SIGNAL(packetReceived(const QByteArray&)), this, SLOT(recvPacket(QByteArray)), Qt::QueuedConnection);
	connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));
	connect(PluginManagerClient::instance(), SIGNAL(sendPacket(QByteArray)), this, SLOT(sendPacket(QByteArray)));
}

void NetworkManager::tryToConnect()
{
	if (state() != QAbstractSocket::UnconnectedState)
		return;

	LocalSettings settings;
	if (settings.value("Network/Server").toString().isEmpty() == true || settings.value("Network/Port").toString().isEmpty() == true)
	{
		qWarning() << tr("Server's hostname or port unspecified, please review your settings.");
		_status = DISCONNECTED;
		emit statusChange(_status);
		return;
	}

	connectToHostEncrypted(settings.value("Network/Server").toString(), settings.value("Network/Port").toUInt());
	if ( ! waitForEncrypted(5000))
		return;

	_status = CONNECTED;
	emit statusChange(_status);
}

void NetworkManager::loginPassword(const QString login, const QString pass)
{
	CommLogin  l(CommLogin::LOGIN_PASSWORD);
	l.login = login;
	l.password = QCryptographicHash::hash(pass.toAscii(), QCryptographicHash::Sha1);
	sendPacket(l.getPacket());
}

void NetworkManager::loginSession(const QString login, const QByteArray session)
{
	CommLogin  l(CommLogin::LOGIN_SESSION);
	l.login = login;
	l.sessionString = session;
	sendPacket(l.getPacket());
}

void NetworkManager::logout()
{
	sendPacket( CommLogin(CommLogin::LOGOUT).getPacket() );
}

void NetworkManager::socketError(QAbstractSocket::SocketError error)
{
	qDebug() << error;
	_status = DISCONNECTED;
	emit statusChange(_status);
}

void NetworkManager::recvPacket(const QByteArray packet)
{
	static PacketDirection recvDirections[] =
	{
		0,//for CommPacket::UNDEFINED
		&NetworkManager::recvError,
		&NetworkManager::recvInit,
		&NetworkManager::recvAlive,
		&NetworkManager::recvLogin,
		&NetworkManager::recvData,
		&NetworkManager::recvPlugin
	};

	_recvPacket = packet;
	CommPacket cp(_recvPacket);
	if (cp.packetType != CommPacket::UNDEFINED)
		(this->*recvDirections[ cp.packetType ])();
}

void NetworkManager::recvError()
{
	CommError err(_recvPacket);
}

void NetworkManager::recvInit()
{
	CommInit i(_recvPacket);
	i.fromName = CLIENT_NAME;
	sendPacket(i.getPacket());
	_status = ESTABLISHED;
	emit statusChange(_status);
}

void NetworkManager::recvAlive()
{
}

void NetworkManager::recvLogin()
{
	CommLogin l(_recvPacket);

	if (l.method == CommLogin::ACCEPTED)
	{
		PluginManagerClient::instance()->setCurrentUser(l.user);

		QDateTime sessionEnd = l.sessionEnd;
		sessionEnd.addSecs(QDateTime::currentDateTime().secsTo(l.serverDateTime));
		UserCache* cache = CacheManager::instance()->userCache(l.login);
		cache->setLastSession(l.sessionString, sessionEnd);

		_nbrDatasForUpdate = l.nbrDataForUpdate;
		_nbrDatasForUpdateReceived = 0;

		qDebug() << tr("NetworkManager::recvLogin seconds between client and server:") << QDateTime::currentDateTime().secsTo(l.serverDateTime);

		_status = LOGGED_IN;
		emit statusChange(_status);
	}
	else if (l.method == CommLogin::REFUSED)
	{
		_status = ESTABLISHED;
		emit statusChange(_status);
	}
}

void NetworkManager::recvData()
{
	CommData data(_recvPacket);

	foreach (DataPlugin* plugin, PluginManagerClient::instance()->findPlugins<DataPlugin*>())
		if (plugin->dataType() == data.type)
		{
			QMetaObject::invokeMethod((QObject*)plugin->dataManager, "receiveData", Q_ARG(const QByteArray, data.data));
			break;
		}
	if (_nbrDatasForUpdate)
	{
		_nbrDatasForUpdateReceived++;
		emit updateProgressChange(_nbrDatasForUpdateReceived * 100 / _nbrDatasForUpdate);
		if (_nbrDatasForUpdate <= _nbrDatasForUpdateReceived)
		{
			_nbrDatasForUpdate = 0;
			emit updateFinished();
		}
	}
}

void NetworkManager::recvPlugin()
{
	CommPlugin p(_recvPacket);

	NetworkPlugin *plugin = PluginManagerClient::instance()->findPlugin<NetworkPlugin*>( p.packet.targetPlugin );
	if ( ! plugin)
	{
		qDebug() << tr("NetworkManager::recvPlugin() cannot find") << p.packet.targetPlugin << tr("plugin.");
		return;
	}
	qRegisterMetaType<PluginPacket>("PluginPacket");
	QMetaObject::invokeMethod(plugin, "receivePacket", Qt::QueuedConnection, Q_ARG(PluginPacket, p.packet));
}
