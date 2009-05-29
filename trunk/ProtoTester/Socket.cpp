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

QCryptographicHash crypto(QCryptographicHash::Sha1);

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
    l.sha1Pass = QByteArray::fromHex("4e1243bd22c66e76c2ba9eddc1f91394e57f9f83");
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

    case 2:
        QVariantHash h;
        h["Request"] = "changePassword";
        crypto.reset();
        crypto.addData("");
        h["password"] = crypto.result();
        //send plugin
        CommPlugin mod(PluginPacket("UserManagment", h));
        mod.packet.packetVersion = 42;
        mod.packet.sourcePlugin = "protoTester";
        sendPacket(mod.getPacket());
        qDebug() << "[out]" << mod;
        break;
    }
}

void Socket::PacketFile()
{
    CommFile f(packet);
    qDebug() << "[ in]" << f;

    fileTransfert.setProtocol(QSsl::SslV3);
    //TODO later: For test
    fileTransfert.setPeerVerifyMode(QSslSocket::VerifyNone);

    fileTransfert.connectToHostEncrypted(host, 42042);
    fileTransfert.waitForEncrypted();
    qDebug() << f.key.toHex() << f.key.length();
    fileTransfert.write(f.key);
    fileTransfert.flush();
    while (fileTransfert.waitForReadyRead())
        qDebug() << fileTransfert.readAll();
}

void Socket::PacketSettings()
{
    CommSettings s(packet);
    qDebug() << "[ in]" << s;

    CommFile f(CommFile::CONTENT_REQUEST, 0);
    sendPacket(f.getPacket());
    qDebug() << "[out]" << f;
}

void Socket::PacketPlugin()
{
    CommPlugin p(packet);
    qDebug() << "[ in]" << p << p.packet.data;
/*
    QHash<QString, QVariant> h;
    h["int"] = 12345;
    h["txt"] = "asdasdasdasdasdasdoiu";
*/
    //send settings
    CommSettings settings;
    settings.method = CommSettings::SET;
    settings.scope = CommSettings::CLIENT_USER_SCOPE;
    settings.plugin = "test";
    settings.setVariantSettings("test");
//    settings.setVariantSettings(h);
    sendPacket(settings.getPacket());
    qDebug() << "[out]" << settings;

//    settings.method = CommSettings::GET;
//    sendPacket(settings.getPacket());
//    qDebug() << "[out]" << settings;
}
