#include "ThreadPacket.h"
#include "Server.h"

ThreadPacket::ThreadPacket(ClientSocket* cs)
{
    client = cs;
    finishReadingFlag = false;
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

    finishReading();

    emit threadFinished();
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
}

void ThreadPacket::PacketInit()
{
    CommInit init;
    client->stream >> init;
}

void ThreadPacket::PacketAlive()
{
}

void ThreadPacket::PacketLogin()
{
    CommLogin login;
    client->stream >> login;
//    if (client->state == ClientSocket::INIT)
//        errorNotInit();
}

void ThreadPacket::PacketFile()
{
}

void ThreadPacket::PacketConfig()
{
}

void ThreadPacket::PacketModule()
{
    //static int i = 0;
    //int j = i++;
    CommModule mod;
    client->stream >> mod;
    finishReading();
    sleep(1);
}

void ThreadPacket::errorNotInit()
{
    client->writeStream.lock();
    CommError err(CommError::NOT_INITIALIZED, "Protocol error: Connexion not intialized.");
    client->writeStream.unlock();
}

void ThreadPacket::finishReading()
{
    if ( ! finishReadingFlag)
        emit readFinished();
    finishReadingFlag = true;
}
