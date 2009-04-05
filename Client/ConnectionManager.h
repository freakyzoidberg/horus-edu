#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include "../Common/CommunicationContainer.h"
#include <QTcpSocket>
#include <QtGui>


class ConnectionManager : public QTcpSocket
{
    Q_OBJECT

    public:
        ConnectionManager();
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

#endif // CONNECTIONMANAGER_H
