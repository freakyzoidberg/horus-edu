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
#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QCryptographicHash>
#include <QHostAddress>

#include "SecondaryThread.h"
#include "../Common/CommSocket.h"

//! This Object manages the client network.
class NetworkManager : public CommSocket
{
    Q_OBJECT

public:
	static NetworkManager*	instance();
	enum					Status { DISCONNECTED, CONNECTED, ESTABLISHED, LOGGED_IN };
	inline Status			status() { return _status; }
	inline bool				isUpdated() { return _isUpdated; }

public slots:
	void	tryToConnect();
	void	loginPassword(const QString login, const QString pass);
	void	loginSession(const QString login, const QByteArray session);
	void	logout();

signals:
	void	statusChange(NetworkManager::Status);
	void	updateProgressChange(int progress);
	void	updateFinished();

private slots:
	//! display the socket errors
	void    socketError(QAbstractSocket::SocketError);
	void	recvPacket(const QByteArray packet);

private:
	Status			_status;
	bool			_isUpdated;
	QByteArray		_recvPacket;
	quint32			_nbrDatasForUpdate;
	quint32			_nbrDatasForUpdateReceived;

	NetworkManager();
	~NetworkManager() {}

	void		setStatus(Status status);
	void        recvError();
	void        recvInit();
	void        recvAlive();
	void        recvLogin();
	void        recvData();
	void        recvPlugin();
};

QDebug operator<<(QDebug, const NetworkManager::Status&);

typedef void(NetworkManager::*PacketDirection)();


#endif // NETWORKMANAGER_H
