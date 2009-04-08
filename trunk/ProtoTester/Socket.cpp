#include "Socket.h"
#include "../Common/Defines.h"
#include "../Common/CommInit.h"
#include "../Common/CommLogin.h"
#include "../Common/CommModule.h"
#include "../Common/CommPacket.h"

#include <QCoreApplication>

Socket::Socket(const char* host, quint16 port)
{
    connect(this, SIGNAL(readyRead()),    SLOT(onReceve()));
    connect(this, SIGNAL(disconnected()), QCoreApplication::instance(), SLOT(quit()));

    connectToHost(host, port);
    stream.setDevice(this);

    qDebug() << "Connect to " << host << ":" << port << " -> " << isOpen();
}

void Socket::onReceve()
{
    disconnect(this, SIGNAL(readyRead()), 0, 0);

    CommPacket pac;
    stream >> pac;
    // check packet is init
    CommInit init;
    stream >> init;

    init.fromName = "Protocol Tester";
    stream << init;

    CommLogin  login(CommLogin::LOGIN, "super-Menteur"); // type de login/logout/...
    stream << login;

    CommModule mod("mod Source", "v42", "mod Destination");
    stream << mod;
    stream << mod;
    stream << mod;

    //connect(this, SIGNAL(readyRead()),    SLOT(onReceve()));
}
