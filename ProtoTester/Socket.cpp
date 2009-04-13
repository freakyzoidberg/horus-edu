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

void Socket::onReceve()
{
    disconnect(this, SIGNAL(readyRead()), 0, 0);

    CommPacket pac;
    stream >> pac;
    // check packet is init

    CommLogin  login;
    login.loginType = CommLogin::LOGIN_PASSWORD;
    login.login = "super-Menteur";
//    login.sha1Pass = ;
    login.sha1Pass = QByteArray::fromHex("4e1243bd22c66e76c2ba9eddc1f91394e57f9f83");
//    stream << login;



    CommInit init;
    stream >> init;

    init.fromName = "Protocol Tester";
    stream << init;

    stream << login;

    CommModule mod("mod Source", "v42", "mod Destination", "data");
    stream << mod;
    stream << mod;
    stream << mod;
    stream << mod;
    stream << mod;
    stream << mod;

    //connect(this, SIGNAL(readyRead()),    SLOT(onReceve()));
    disconnectFromHost();
}
