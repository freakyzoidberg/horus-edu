#include "CommSocket.h"
#include <QtEndian>

CommSocket::CommSocket(QObject* parent) : QTcpSocket(parent)
{
    sizePacket = 0;
    connect(this, SIGNAL(readyRead()), this, SLOT(bytesReceived()));
    qDebug() << readBufferSize();
}

void CommSocket::bytesReceived()
{
    if ( ! sizePacket)
    {
        if ((quint32)bytesAvailable() < sizeof(sizePacket))
            return;
        read((char*)&sizePacket, sizeof(sizePacket));
        sizePacket = qFromLittleEndian(sizePacket);
    }

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
    quint32 size = qToLittleEndian(pac.length());
    write((char*)&size, sizeof(size));
    write(pac.data(), size);
}
