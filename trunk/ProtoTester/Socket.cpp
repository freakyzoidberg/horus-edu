#include "Socket.h"
#include "../Common/Defines.h"
#include "../Common/CommInit.h"
#include "../Common/CommLogin.h"
#include "../Common/CommPlugin.h"
#include "../Common/CommPacket.h"
#include "../Common/CommSettings.h"

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

    //read init
    CommPacket pac(packet);
    CommInit   init(packet);
    qDebug() << "[ in]" << init;

    //send init
    init.fromName = "Protocol Tester";
    sendPacket(init.getPacket());
    qDebug() << "[out]" << init;

    //send login
    CommLogin  l(CommLogin::LOGIN_PASSWORD);
    l.login = "super-Menteur";
    //l.login = QString::fromUtf8("toto42`~!@#$%^&*()-_=+' \";:汉语");
    l.sha1Pass = QByteArray::fromHex("4e1243bd22c66e76c2ba9eddc1f91394e57f9f83");
    sendPacket(l.getPacket());
    qDebug() << "[out]" << l;


    QHash<QString, QVariant> h;
    h["int"] = 12345;
    h["txt"] = "asdasdasdasdasdasdoiu";


    //send plugin
    CommPlugin mod(PluginPacket("TestComm", h));
    mod.packet.packetVersion = 42;
    mod.packet.sourcePlugin = "protoTester";
    sendPacket(mod.getPacket());
    qDebug() << "[out]" << mod;
/*
    sendPacket(mod.getPacket());
    qDebug() << "[out]" << mod;
    sendPacket(mod.getPacket());
    qDebug() << "[out]" << mod;
*/


    //send settings
    CommSettings settings;
    settings.method = CommSettings::SET;
    settings.scope = CommSettings::CLIENT_USER_SCOPE;
    settings.plugin = "test";
    settings.setVariantSettings(h);
    sendPacket(settings.getPacket());
    qDebug() << "[out]" << settings;
/*
    settings.method = CommSettings::GET;
    sendPacket(settings.getPacket());
    qDebug() << "[out]" << settings;
*/
    disconnectFromHost();
}
