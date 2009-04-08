#ifndef THREADPACKET_H
#define THREADPACKET_H

#include <QRunnable>

#include "ClientSocket.h"
#include "../Common/CommInit.h"
#include "../Common/CommError.h"
#include "../Common/CommLogin.h"
#include "../Common/CommModule.h"
#include "../Common/CommPacket.h"

class ThreadPacket : public QObject, public QRunnable
{
public:
    ThreadPacket(ClientSocket* cs);
    ~ThreadPacket();
    void run();
    void PacketUnknow();
    void PacketError();
    void PacketInit();
    void PacketAlive();
    void PacketLogin();
    void PacketFile();
    void PacketConfig();
    void PacketModule();

private:
    ClientSocket* client;
    static const quint8 packetDirectionsNumber;
    static void (ThreadPacket::*packetDirections[]) ();
};

typedef void(ThreadPacket::*packetDirection)();

#endif // THREADPACKET_H
