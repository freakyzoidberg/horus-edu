#include "CommSocket.h"

CommSocket::CommSocket(QObject* parent) : QTcpSocket(parent)
{
    sizePacket = 0;
    connect(this, SIGNAL(readyRead()), this, SLOT(bytesReceived()));
}

void CommSocket::bytesReceived()
{
    if ( ! bytesAvailable())
        return;

    if ( ! sizePacket)
        read((char*)&sizePacket, sizeof(sizePacket));

    if (bytesAvailable() < sizePacket)
        return;

    QByteArray pac(sizePacket, 0);
    read(pac.data(), sizePacket);

//    recvQueue.push_back(pac);
    sizePacket = 0;

    emit packetReceived(pac);
    emit readyRead();
}

void CommSocket::sendPacket(QByteArray pac)
{
/*    sendQueueMutex.lock();
    sendQueue.push_back(pac);
    sendQueueMutex.unlock();*/

    quint32 size = pac.length();
    write((char*)&size, sizeof(size));
    write(pac.data(), size);


//    emit packetToSend();
}
/*
void CommSocket::sendPackets()
{
    sendQueueMutex.lock();
    if ( ! sendQueue.length())
        return sendQueueMutex.unlock();

    QByteArray& pac = sendQueue.first();
    quint32 size = pac.length();
    write((char*)&size, sizeof(size));
    write(pac.data(), size);
    sendQueue.pop_front();
    sendQueueMutex.unlock();
    emit packetToSend();
}
*/
