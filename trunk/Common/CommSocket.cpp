#include "CommSocket.h"

CommSocket::CommSocket(QObject* parent) : QTcpSocket(parent)
{
    sizePacket = 0;
    connect(this, SIGNAL(readyRead()), this, SLOT(bytesReceived()));
}

void CommSocket::bytesReceived()
{
    if ((quint32)bytesAvailable() < sizeof(sizePacket))
        return;

    if ( ! sizePacket)
        read((char*)&sizePacket, sizeof(sizePacket));

    if (bytesAvailable() < sizePacket)
        return;

    QByteArray pac(sizePacket, 0);
    read(pac.data(), sizePacket);

    sizePacket = 0;

    emit packetReceived(pac);
    emit readyRead();
}

void CommSocket::sendPacket(const QByteArray& pac)
{
    quint32 size = pac.length();
    write((char*)&size, sizeof(size));
    write(pac.data(), size);
}
