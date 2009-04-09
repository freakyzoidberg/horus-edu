#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QTcpSocket>
#include <QtGui>


class NetworkManager : public QTcpSocket
{
    Q_OBJECT

    public:
        NetworkManager();
        void    ConnectTo(QString addr, int port);
    private slots:
        void    readData();
        void    writeData();
        void   displayError(QAbstractSocket::SocketError);
    private:
        QTcpSocket *tcpSocket;
        quint16     blockSize;
        QString currentFortune;
};

#endif // NETWORKMANAGER_H
