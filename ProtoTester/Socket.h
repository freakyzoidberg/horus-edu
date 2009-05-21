#ifndef SOCKET_H
#define SOCKET_H

#include "../Common/CommSocket.h"

class Socket : public CommSocket
{
  Q_OBJECT

public:
    Socket(const char*, quint16);
    QDataStream stream;

public slots:
    void packetAvailable(const QByteArray&);

private:
    void PacketUndefined();
    void PacketError();
    void PacketInit();
    void PacketAlive();
    void PacketLogin();
    void PacketFile();
    void PacketSettings();
    void PacketPlugin();

    QByteArray packet;

    //! corespondance table between CommPacket::type and the methods
    static void (Socket::*packetDirections[]) ();
};

typedef void(Socket::*packetDirection)();

#endif // SOCKET_H
