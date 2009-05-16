#include "SimpMessage.h"

Q_EXPORT_PLUGIN2(SimpMessage, SimpMessage)

SimpMessage::SimpMessage()
{
    qDebug() << "He Ho !! je suis la!!!";
}

SimpMessage::~SimpMessage()
{
    qDebug() << "gniiiiiiiiIIIIIII";
}

void SimpMessage::recvPacket(quint32 userId, const PluginPacket& packet) const
{
    server->sendPacket(userId, PluginPacket(packet.sourcePlugin, packet.data));
}
