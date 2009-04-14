#include "Socket.h"
#include "../Common/Defines.h"
#include "../Common/CommInit.h"
#include "../Common/CommLogin.h"
#include "../Common/CommModule.h"
#include "../Common/CommPacket.h"

#include <QCoreApplication>

Socket::Socket(const char* host, quint16 port) : CommSocket()
{
    connect(this, SIGNAL(packetReceived(QByteArray)), this, SLOT(packetAvailable(QByteArray)));
    connect(this, SIGNAL(disconnected()), QCoreApplication::instance(), SLOT(quit()));
    //connect(this, SIGNAL(error(QAbstractSocket::SocketError)), QCoreApplication::instance(), SLOT(quit()));
    //connect(this, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChangedSlot(QAbstractSocket::SocketState)));

    connectToHost(host, port);

    qDebug() << "Connect to " << host << ":" << port << " -> " << isOpen() << isReadable() << isValid() << isWritable() << state();
    stream.setDevice(this);
}

void Socket::stateChangedSlot(QAbstractSocket::SocketState s)
{
    qDebug() << s;
}

void Socket::packetAvailable(QByteArray packet)
{
    disconnect(this, SIGNAL(packetReceived(QByteArray)), 0, 0);

    CommPacket pac(packet);
    CommInit   init(packet);
    qDebug() << "[ in]" << init;

    init.fromName = "Protocol Tester";
    sendPacket(init.getPacket());
    qDebug() << "[out]" << init;

    CommLogin  l(CommLogin::LOGIN_PASSWORD);
    l.login = "super-Menteur";
    l.sha1Pass = QByteArray::fromHex("4e1243bd22c66e76c2ba9eddc1f91394e57f9f83");
    sendPacket(l.getPacket());
    qDebug() << "[out]" << l;

    sendPacket(init.getPacket());
    qDebug() << "[out]" << init;

    sendPacket(l.getPacket());
    qDebug() << "[out]" << l;

    CommModule mod("mod Source", "v42", "mod Destination", "data");
    sendPacket(mod.getPacket());
    qDebug() << "[out]" << mod;
    sendPacket(mod.getPacket());
    qDebug() << "[out]" << mod;
    sendPacket(mod.getPacket());
    qDebug() << "[out]" << mod;
    sendPacket(mod.getPacket());
    qDebug() << "[out]" << mod;
    sendPacket(mod.getPacket());
    qDebug() << "[out]" << mod;
    sendPacket(mod.getPacket());
    qDebug() << "[out]" << mod;

    //connect(this, SIGNAL(readyRead()),    SLOT(onReceve()));
//    sleep(1);
    disconnectFromHost();
}
