#ifndef THREADPACKET_H
#define THREADPACKET_H

#include <QRunnable>

#include "ClientSocket.h"
#include "../Common/CommInit.h"
#include "../Common/CommError.h"
#include "../Common/CommLogin.h"
#include "../Common/CommModule.h"
#include "../Common/CommPacket.h"

class ThreadPacket : public QRunnable
{
public:
    ThreadPacket(ClientSocket* cs);

    void run();

private:
    void PacketError();
    void PacketInit();
    void PacketAlive();
    void PacketLogin();
    void PacketFile();
    void PacketConfig();
    void PacketModule();

    void errorNotInit();

    ClientSocket* client;

    static void (ThreadPacket::*packetDirections[]) ();
};

typedef void(ThreadPacket::*packetDirection)();

#endif // THREADPACKET_H
