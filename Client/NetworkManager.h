#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QCryptographicHash>
#include <QHostAddress>

#include "../Common/CommSocket.h"
#include    "PacketManager.h"
#include "AbstractManager.h"

//! This Object manages the client network.
class NetworkManager : public CommSocket, public AbstractManager
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
        //! stop network
        void    quit();
    private:
        //! packetManager to read the received packet
        PacketManager   *packManag;
};

#endif // NETWORKMANAGER_H
