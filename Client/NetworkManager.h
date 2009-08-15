#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QCryptographicHash>
#include <QHostAddress>

#include "../Common/AbstractManager.h"
#include "../Common/CommSocket.h"

#include "PacketManager.h"

//! This Object manages the client network.
class NetworkManager : public AbstractManager
{
    Q_OBJECT

    public:
        NetworkManager();
        ~NetworkManager();
    protected slots:
        //! event loop
        bool    event(QEvent *e);
    private slots:
        //! display the socket errors
        void    displayError(QAbstractSocket::SocketError);
		void	log();
		void	waitUserPass();
        //! stop network
        void    quit();
    private:
        //! packetManager to read the received packet
        PacketManager   *packManag;
		CommSocket		*socket;
};

#endif // NETWORKMANAGER_H
