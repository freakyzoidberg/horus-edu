#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QTcpSocket>
#include <QtGui>
#include <QCryptographicHash>

#include    "StartEvent.h"
#include    "StopEvent.h"
#include    "PacketManager.h"


class NetworkManager : public QTcpSocket
{
    Q_OBJECT

    public:
        NetworkManager(QObject *parent);
        void    ConnectTo(QString addr, int port);
        void    loginServer();
    private slots:
        void    readData();
        void    displayError(QAbstractSocket::SocketError);
        bool    event(QEvent *e);
        bool    quit();
    private:
        QTcpSocket *tcpSocket;
        QDataStream stream;
        PacketManager   *packManag;
        CommPacket  protoPac;
};

#endif // NETWORKMANAGER_H
