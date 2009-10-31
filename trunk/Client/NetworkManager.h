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
	QByteArray		_recvPacket;
	quint32			_nbrDatasForUpdate;
	quint32			_nbrDatasForUpdateReceived;

	NetworkManager();
	~NetworkManager() {}

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
