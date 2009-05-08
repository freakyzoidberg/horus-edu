#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QtGui>
#include <QCryptographicHash>
#include <QHostAddress>

#include "../Common/CommSocket.h"

#include    "StartEvent.h"
#include    "StopEvent.h"
#include    "PacketManager.h"

class NetworkManager : public CommSocket //, public QThread
{
    Q_OBJECT

    public:
        NetworkManager(QObject *parent = 0);
        void    ConnectTo(QString addr, int port);

        protected:
        void run();

    private slots:
        void    displayError(QAbstractSocket::SocketError);
        bool    event(QEvent *e);
        bool    quit();

    private:
        PacketManager   packManag;
};

#endif // NETWORKMANAGER_H
