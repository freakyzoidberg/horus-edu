#include "PacketManager.h"

PacketManager::PacketManager(QTcpSocket *sock)
{
    streamSock.setDevice(sock);
}

packetDirection PacketManager::packetDirections[] =
{
    0,//for CommPacket::UNKNOW
    &PacketManager::PacketError,
    &PacketManager::PacketInit,
    &PacketManager::PacketAlive,
    &PacketManager::PacketLogin,
    &PacketManager::PacketFile,
    &PacketManager::PacketConfig,
    &PacketManager::PacketModule
};

void    PacketManager::receivedData(const CommPacket &protoPac)
{
    if (protoPac.packetType != CommPacket::UNKNOW)
        (this->*packetDirections[ protoPac.packetType ])();
}

void PacketManager::PacketError()
{
    CommError err;
    streamSock >> err;
}

void PacketManager::PacketInit()
{
    CommInit init;
    streamSock >> init;
}

void PacketManager::PacketAlive()
{
}

void PacketManager::PacketLogin()
{
    CommLogin login;
    streamSock >> login;
}

void PacketManager::PacketFile()
{
}

void PacketManager::PacketConfig()
{
}

void PacketManager::PacketModule()
{
    static int i = 0;
    int j = i++;
    CommModule mod;
    streamSock >> mod;

    qDebug() << "a long work start (2s) no:" << j;
    sleep(2);
    qDebug() << "a long work end no:" << j;
}
