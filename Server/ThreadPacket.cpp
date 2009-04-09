#include "ThreadPacket.h"
#include "Server.h"

ThreadPacket::ThreadPacket(ClientSocket* cs)
{
    client = cs;
}

void ThreadPacket::run()
{
    CommPacket pac;

    quint32 n;
    // Look for a valid header
    for (n=0; client->socket.bytesAvailable(); n++)
    {
        client->stream >> pac;
        if (pac.packetType != CommPacket::UNKNOW)
            break;
    }

    //if invalid packets are found
    if (n)
        qDebug() << n << "unknow packets received from client" << client->id;

    // and redirect to the good method
    if (pac.packetType != CommPacket::UNKNOW)
        (this->*packetDirections[ pac.packetType ])();
    else
        client->readFinished();

    client->threadFinished();
}

packetDirection ThreadPacket::packetDirections[] =
{
    0,//for CommPacket::UNKNOW
    &ThreadPacket::PacketError,
    &ThreadPacket::PacketInit,
    &ThreadPacket::PacketAlive,
    &ThreadPacket::PacketLogin,
    &ThreadPacket::PacketFile,
    &ThreadPacket::PacketConfig,
    &ThreadPacket::PacketModule
};

void ThreadPacket::PacketError()
{
    CommError err;
    client->stream >> err;
    client->readFinished();
}

void ThreadPacket::PacketInit()
{
    CommInit init;
    client->stream >> init;
    client->readFinished();
}

void ThreadPacket::PacketAlive()
{
    client->readFinished();
}

void ThreadPacket::PacketLogin()
{
    CommLogin login;
    client->stream >> login;
//    if (client->state == ClientSocket::INIT)
//        errorNotInit();
    client->readFinished();
}

void ThreadPacket::PacketFile()
{
    client->readFinished();
}

void ThreadPacket::PacketConfig()
{
    client->readFinished();
}

void ThreadPacket::PacketModule()
{
    //static int i = 0;
    //int j = i++;
    CommModule mod;
    client->stream >> mod;
    client->readFinished();
    sleep(1);
}

void ThreadPacket::errorNotInit()
{
    client->writeStream.lock();
    CommError err(CommError::NOT_INITIALIZED, "Protocol error: Connexion not intialized.");
    client->writeStream.unlock();
}
