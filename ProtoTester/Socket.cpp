#include "Socket.h"
#include "../Common/Defines.h"
#include "../Common/CommInit.h"
#include "../Common/CommError.h"
#include "../Common/CommLogin.h"
#include "../Common/CommFile.h"
#include "../Common/CommPlugin.h"
#include "../Common/CommPacket.h"
#include "../Common/CommSettings.h"

#include <QDebug>
#include <QCoreApplication>
#include <QDateTime>
#include <QVariant>

Socket::Socket(const char* _host, quint16 port) : CommSocket()
{
    host = _host;
    connect(this, SIGNAL(packetReceived(const QByteArray&)), this, SLOT(packetAvailable(const QByteArray&)));
    connect(this, SIGNAL(disconnected()), QCoreApplication::instance(), SLOT(quit()));

    connectToHostEncrypted(host, port);

    qDebug() << "Connect to " << host << ":" << port << " -> " << isOpen() << isReadable() << isValid() << isWritable() << state();
    stream.setDevice(this);
}

void Socket::packetAvailable(const QByteArray& _packet)
{
    packet = _packet;

    CommPacket pac(packet);
    // redirect to the good method
    return (this->*packetDirections[ pac.packetType ])();
//    disconnectFromHost();
}

packetDirection Socket::packetDirections[] =
{
    &Socket::PacketUndefined,
    &Socket::PacketError,
    &Socket::PacketInit,
    &Socket::PacketAlive,
    &Socket::PacketLogin,
    &Socket::PacketFile,
    &Socket::PacketSettings,
    &Socket::PacketPlugin
};

void Socket::PacketUndefined()
{
    CommPacket p(CommPacket::UNDEFINED);
    qDebug() << "[ in]" << p;
}

void Socket::PacketError()
{
    CommError err(packet);
    qDebug() << "[ in]" << err;
}

void Socket::PacketInit()
{
    //read init
    CommInit   init(packet);
    qDebug() << "[ in]" << init;

    //send init
    init.fromName = "Protocol Tester";
    sendPacket(init.getPacket());
    qDebug() << "[out]" << init;

    //send loginqsqld
    CommLogin  l(CommLogin::LOGIN_PASSWORD);
    l.login = "super-Menteur";
    //l.login = QString::fromUtf8("toto42`~!@#$%^&*()-_=+' \";:汉语");
    l.sha1Pass = QCryptographicHash::hash("test", QCryptographicHash::Sha1);
    sendPacket(l.getPacket());
    qDebug() << "[out]" << l;
}

void Socket::PacketAlive()
{
    CommPacket a(CommPacket::ALIVE);
    qDebug() << "[ in]" << a;
}

void Socket::PacketLogin()
{
    CommLogin l(packet);
    qDebug() << "[ in]" << l;
/*
    static int pass = 0;
    pass++;

    switch (pass)
    {
    case -42://disabled, just for tests
        l.method = CommLogin::LOGOUT;
        sendPacket(l.getPacket());
        qDebug() << "[out]" << l;
        break;

    case 1:
        l.method = CommLogin::LOGIN_SESSION;
        l.login = "super-Menteur";
        sendPacket(l.getPacket());
        qDebug() << "[out]" << l;
        break;

    case 2:*/
//SEND MODULE
    qDebug() << "case 2";
    QVariantHash h;
    h["Request"] = "getNodeInfo";
    //send plugin
    CommPlugin mod(PluginPacket("TreeManagement", h));
    mod.packet.packetVersion = 0;
    mod.packet.sourcePlugin = "protoTester";
    sendPacket(mod.getPacket());
    qDebug() << "[out]" << mod;

//SEND SETTINGS
    CommSettings settings;
    settings.method = CommSettings::SET;
    settings.scope = CommSettings::CLIENT_USER_SCOPE;
    settings.plugin = "test";
    settings.setVariantSettings("test");
//    settings.setVariantSettings(h);
    sendPacket(settings.getPacket());
    qDebug() << "[out]" << settings;


//SEND FILE REQUEST
    CommFile f(CommFile::NEW_FILE);
    f.fileInfo.fileName = "test.txt";
    f.fileInfo.nodeId = 0;
    f.mode = QIODevice::ReadWrite;
    sendPacket(f.getPacket());
    qDebug() << "[out]" << f;
    /*
        h["Request"] = "changePassword";
        h["OldPassword"] = QByteArray::fromHex("4e1243bd22c66e76c2ba9eddc1f91394e57f9f83");
        h["password"] = QCryptographicHash::hash("test", QCryptographicHash::Sha1);
        //send plugin
        CommPlugin mod2(PluginPacket("UserManagment", h));
        mod2.packet.packetVersion = 0;
        mod2.packet.sourcePlugin = "protoTester";
        sendPacket(mod2.getPacket());
        qDebug() << "[out]" << mod2;
*/
//        break;
//    }
}

void Socket::PacketFile()
{
    CommFile f(packet);
    qDebug() << "[ in]" << f;

    if (f.error != CommFile::NO_ERROR)
        return;

    fileTransfert.setProtocol(QSsl::SslV3);
    //TODO later: For test
    fileTransfert.setPeerVerifyMode(QSslSocket::VerifyNone);

    fileTransfert.connectToHostEncrypted(host, 42042);
    fileTransfert.waitForEncrypted();
    qDebug() << f.key.toHex() << f.key.length();
    fileTransfert.write(f.key);
    fileTransfert.flush();
    qDebug() << "read file:";

    while (fileTransfert.waitForReadyRead(100) && fileTransfert.bytesAvailable())
        qDebug() << fileTransfert.readAll();

    fileTransfert.write("1234567890abcdef");
}

void Socket::PacketSettings()
{
    CommSettings s(packet);
    qDebug() << "[ in]" << s;
}

void Socket::PacketPlugin()
{
    CommPlugin p(packet);
    qDebug() << "[ in]" << p << p.packet.data;
}
