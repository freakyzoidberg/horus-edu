#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QtGui>
#include <QCryptographicHash>
#include <QHostAddress>

#include "../Common/CommSocket.h"

#include    "PacketManager.h"
#include    "PacketSender.h"
#include    "ClientEvents.h"
#include    "LoginDialog.h"

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
    protected slots:
        bool    event(QEvent *e);
    private slots:
        void    displayError(QAbstractSocket::SocketError);
        bool    quit();

    private:
        PacketManager   *packManag;
        PacketSender   *packSend;
        static bool instanceFlag;
        static NetworkManager *single;
        QWidget *ld;
};

#endif // NETWORKMANAGER_H
