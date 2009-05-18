#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QtGui>
#include <QCryptographicHash>
#include <QHostAddress>

#include "../Common/CommSocket.h"

#include    "PacketManager.h"
#include    "ClientEvents.h"
#include    "LoginDialog.h"

//! This Object is a singleton class, it manages the client network.
class NetworkManager : public CommSocket //, public QThread
{
    Q_OBJECT

    public:
        NetworkManager(QObject *parent = 0);
        //! method to get the singleton instance
        static  NetworkManager* getInstance(QObject *parent);
        ~NetworkManager();
    protected:
        void run();
    protected slots:
        //! event loop
        bool    event(QEvent *e);
        //!
        void    lwState(bool st);
    private slots:
        //! display the socket errors
        void    displayError(QAbstractSocket::SocketError);
        bool    quit();

    private:
        //! packetManager to read the received packet
        PacketManager   *packManag;
        //! flag for the singleton
        static bool instanceFlag;
        //! the instance of the singleton
        static NetworkManager *single;
        //! login window
        QWidget *ld;
};

#endif // NETWORKMANAGER_H
