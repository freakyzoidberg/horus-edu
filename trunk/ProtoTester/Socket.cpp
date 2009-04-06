#include "Socket.h"
#include "../Common/Defines.h"
#include "../Common/CommInit.h"
#include "../Common/CommLogin.h"
#include "../Common/CommModule.h"
#include "../Common/CommPacket.h"

#include <QCoreApplication>

Socket::Socket(const char* host, quint16 port)
{
    connect(this, SIGNAL(readyRead()),    SLOT(onReceveInit()));
    connect(this, SIGNAL(disconnected()), QCoreApplication::instance(), SLOT(quit()));

    connectToHost(host, port);
    stream.setDevice(this);

    qDebug() << "Connect to " << host << ":" << port << " -> " << isOpen();
}

void Socket::onReceveInit()
{
    disconnect(this, SIGNAL(readyRead()), 0, 0);

    CommInit init;
    stream >> init;
    init.fromName = "Protocol Tester";
    stream << init;

    CommPacket pac(CommPacket::LOGIN);//TYPE de packet
    CommLogin  login(CommLogin::LOGIN, "super-Menteur"); // type de login/logout/...
    stream << pac << login;

    CommPacket pacm(CommPacket::MODULE);//TYPE de packet
    CommModule mod("mod Source", "v42", "mod Destination");
    stream << pacm << mod;
    stream << pacm << mod;
    stream << pacm << mod;
    stream << pacm << mod;
    stream << pacm << mod;
    stream << pacm << mod;
    stream << pacm << mod;
    stream << pacm << mod;
    stream << pacm << mod;

    connect(this, SIGNAL(readyRead()),    SLOT(onRecevePacket()));
}

void Socket::onRecevePacket()
{
}
