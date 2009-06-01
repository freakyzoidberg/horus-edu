#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QtGui>
#include <QCryptographicHash>
#include <QHostAddress>

#include "../Common/CommSocket.h"
#include "ClientApplication.h"
#include    "PacketManager.h"
#include    "ClientEvents.h"

//! This Object is a singleton class, it manages the client network.
class NetworkManager : public CommSocket
{
    Q_OBJECT

    public:
        NetworkManager(QObject *parent = 0);
        ~NetworkManager();
        ClientApplication *parent;
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
