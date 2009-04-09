#ifndef PACKETMANAGER_H
#define PACKETMANAGER_H

#include <QTcpSocket>
#include <QtGui>

#include "../Common/Defines.h"
#include "../Common/CommInit.h"
#include "../Common/CommLogin.h"
#include "../Common/CommModule.h"
#include "../Common/CommPacket.h"
#include "../Common/CommError.h"

class   PacketManager
{
    public:
        PacketManager(QTcpSocket *sock);
        void    receivedData(const CommPacket  &protoPac);
        void    PacketError();
        void    PacketInit();
        void    PacketAlive();
        void    PacketLogin();
        void    PacketFile();
        void    PacketConfig();
        void    PacketModule();
    private:
        QDataStream streamSock;
        static void (PacketManager::*packetDirections[]) ();
};

typedef void(PacketManager::*packetDirection)();
#endif // PACKETMANAGER_H
