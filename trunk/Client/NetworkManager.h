#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QtGui>
#include <QCryptographicHash>
#include <QHostAddress>

#include "../Common/CommSocket.h"

#include    "PacketManager.h"
#include    "ClientEvents.h"

class NetworkManager : public CommSocket //, public QThread
{
    Q_OBJECT

    public:
        NetworkManager(QObject *parent = 0);
        void    ConnectTo(QString addr, int port);
        static  NetworkManager* getInstance(QObject *parent);
        void    login(const QString &login, const QString &pass, int ltype);

        ~NetworkManager();
    protected:
        void run();

    private slots:
        void    displayError(QAbstractSocket::SocketError);
        bool    event(QEvent *e);
        bool    quit();

    private:
        PacketManager   packManag;
        static bool instanceFlag;
        static NetworkManager *single;
};

#endif // NETWORKMANAGER_H
