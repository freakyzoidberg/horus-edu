#ifndef THREADPACKET_H
#define THREADPACKET_H

#include <QRunnable>
#include <QObject>

#include "ClientSocket.h"
#include "../Common/CommError.h"

//! This Object is a thread for each packet readed on the client socket
class ThreadPacket : public QObject, public QRunnable
{
  Q_OBJECT

public:
    ThreadPacket(ClientSocket* cs, const QByteArray& pac);

    //! read the first CommPacket and go to the associed method
    /*!
     * read the socket until finding a good CommPacket
     * it's also the entry point of the thread
     */
    void run();

private:
    void PacketUndefined();
    void PacketError();
    void PacketInit();
    void PacketAlive();
    void PacketLogin();
    void PacketFile();
    void PacketSettings();
    void PacketModule();

    void sendError(CommError::Error err, const char* str="");

    ClientSocket* socket;
    QByteArray   packet;

    //! corespondance table between CommPacket::type and the methods
    static void (ThreadPacket::*packetDirections[]) ();

signals:
    void sendPacket(const QByteArray);
};

typedef void(ThreadPacket::*packetDirection)();

#endif // THREADPACKET_H
