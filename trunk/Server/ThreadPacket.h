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

  typedef void(ThreadPacket::*packetDirection)();

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
    void PacketData();
    void PacketPlugin();

    //! send an error to the client
    void sendError(CommError::Error err, const char* str="") const;

    //! a pointer to the parent ClientSocket
    ClientSocket* socket;
    //! the received packet
    /*! every methods of ThreadPacket read and truncate this value
     */
    QByteArray    packet;

    //! corespondance table between CommPacket::type and the methods
    static packetDirection packetDirections[];

signals:
    //! signal emmited when a packet need to be send to the client
    void sendPacket(const QByteArray) const;
    //! signal emmited when a packet need to be send to a client on an other socket (need to be connected first)
    void sendPacketToAnotherSocket(const QByteArray) const;
};

#endif // THREADPACKET_H
