#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QTcpSocket>
#include <QtGui>
#include    "StartEvent.h"
#include    "StopEvent.h"

class NetworkManager : public QTcpSocket
{
    Q_OBJECT

    public:
        NetworkManager(QObject *parent);
        void    ConnectTo(QString addr, int port);
    private slots:
        void    readData();
        void    writeData();
        void   displayError(QAbstractSocket::SocketError);
        bool    event(QEvent *e);
    private:
        QTcpSocket *tcpSocket;
        quint16     blockSize;
        QString currentFortune;
};

#endif // NETWORKMANAGER_H
