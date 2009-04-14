#include "PacketManager.h"

PacketManager::PacketManager(QObject* parent) : QObject(parent)
{
    state = DISCONNECTED;
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

void PacketManager::packetReceived(QByteArray& p)
{
    packet = p;
    CommPacket pac(packet);
    if (pac.packetType != CommPacket::UNKNOW)
        (this->*packetDirections[ pac.packetType ])();
}

void PacketManager::PacketError()
{
    CommError err(packet);
    qDebug() << "[ in]" << err;
}

void PacketManager::PacketInit()
{
    CommInit init(packet);
    qDebug() << "[ in]" << init;
    //TODO add protocol version compatible check
    state = LOGGED_OUT;

    CommLogin l(packet);
    l.login = "super-Menteur";
    l.sha1Pass = QByteArray::fromHex("4e1243bd22c66e76c2ba9eddc1f91394e57f9f83");
    emit sendPacket(l.getPacket());
    qDebug() << "[out]" << l;
}

void PacketManager::PacketAlive()
{
    qDebug() << "[ in] Alive";
}

void PacketManager::PacketLogin()
{
    if (state != LOGGED_OUT)
        return;

    CommLogin l(packet);
    qDebug() << "[ in]" << l;
    //if (l.)
}

void PacketManager::PacketFile()
{
}

void PacketManager::PacketConfig()
{
}

void PacketManager::PacketModule()
{
}
