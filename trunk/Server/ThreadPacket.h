#ifndef THREADPACKET_H
#define THREADPACKET_H

#include <QRunnable>

#include "ClientSocket.h"

class ThreadPacket : public QRunnable
{
public:
    ThreadPacket(ClientSocket* cs);
    void run();
    void PacketUnknow();
    void PacketAlive();
    void PacketLogin();
    void PacketFile();
    void PacketConfig();
    void PacketModule();

//private:
    ClientSocket* client;
    static const quint8 packetDirectionsNumber;
    static void (ThreadPacket::*packetDirections[]) ();
};

typedef void(ThreadPacket::*packetDirection)();

#endif // THREADPACKET_H
