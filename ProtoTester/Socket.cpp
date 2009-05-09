#include "Socket.h"
#include "../Common/Defines.h"
#include "../Common/CommInit.h"
#include "../Common/CommLogin.h"
#include "../Common/CommModule.h"
#include "../Common/CommPacket.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QVariant>

Socket::Socket(const char* host, quint16 port) : CommSocket()
{
    connect(this, SIGNAL(packetReceived(QByteArray)), this, SLOT(packetAvailable(QByteArray)));
    connect(this, SIGNAL(disconnected()), QCoreApplication::instance(), SLOT(quit()));
    //connect(this, SIGNAL(error(QAbstractSocket::SocketError)), QCoreApplication::instance(), SLOT(quit()));
    //connect(this, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChangedSlot(QAbstractSocket::SocketState)));

    connectToHostEncrypted(host, port);

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

    CommModule mod(ModulePacket("TestComm", "data...."));
    mod.packet.packetVersion = 42;
    mod.packet.sourceModule = "protoTester";
    sendPacket(mod.getPacket());
    qDebug() << "[out]" << mod;

    mod.packet.data = 123456789;
    sendPacket(mod.getPacket());
    qDebug() << "[out]" << mod;

    QHash<QString, QVariant> h;
    h["qwe"] = 12345;
    h["000"] = "asdasdasdasdasdasd";
    mod.packet.data = QVariant(h);
    sendPacket(mod.getPacket());
    qDebug() << "[out]" << mod;

    sendPacket(mod.getPacket());
    qDebug() << "[out]" << mod;

    sendPacket(mod.getPacket());
    qDebug() << "[out]" << mod;

    sendPacket(mod.getPacket());
    qDebug() << "[out]" << mod;
    //connect(this, SIGNAL(readyRead()),    SLOT(onReceve()));

    disconnectFromHost();
}
