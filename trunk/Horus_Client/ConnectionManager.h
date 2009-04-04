#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include "../Common/CommunicationContainer.h"
#include <QTcpSocket>

class ConnectionManager
{
    public:
        ConnectionManager();
    private slots:
        void    ConnectTo();
        void    readData();
        void    writeData();
    private:
        QTcpSocket *tcpSocket;
        quint16     blockSize;
};

#endif // CONNECTIONMANAGER_H
