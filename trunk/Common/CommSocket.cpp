#include "CommSocket.h"
#include <QtEndian>
#include <QSsl>

CommSocket::CommSocket(QObject* parent) : QSslSocket(parent)
{
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorSlot(QAbstractSocket::SocketError)));
    connect(this, SIGNAL(sslErrors(QList<QSslError>)),         this, SLOT(sslErrorsSlot(QList<QSslError>)));

    setProtocol(QSsl::SslV3);

    //TODO later: For test
    setPeerVerifyMode(QSslSocket::VerifyNone);

    setLocalCertificate("./ssl/Horus.crt");
    setPrivateKey("./ssl/Horus.key");

    sizePacket = 0;
    connect(this, SIGNAL(readyRead()), this, SLOT(bytesReceived()));
}

void CommSocket::errorSlot(QAbstractSocket::SocketError e)
{
    qDebug() << "error" << e;
}

void CommSocket::sslErrorsSlot(QList<QSslError> e)
{
    qDebug() << "sslError" << e;
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
    flush();
}
