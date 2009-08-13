#include "SimpMessage.h"

Q_EXPORT_PLUGIN2(SimpMessage, SimpMessage)

SimpMessage::SimpMessage()
{
    qDebug() << "SimpMessage has arrived";
}

SimpMessage::~SimpMessage()
{
    qDebug() << "bye bye SimpMessage";
}

void SimpMessage::recvPacket(quint32 userId, const PluginPacket& packet)
{
    server->sendPacket(userId, PluginPacket(packet.sourcePlugin, packet.data));
}
