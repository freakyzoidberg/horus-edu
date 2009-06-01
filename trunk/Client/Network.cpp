#include    <QtGui/QApplication>

#include "ThreadNetwork.h"
#include "Network.h"
#include "../Common/PluginPacket.h"
#include "../Common/CommPlugin.h"

Network::Network()
{
}

void            Network::sendPacket(const PluginPacket& packet) const
{
    CommPlugin p = packet;

    p.packet.packetVersion = plugin->getVersion().toUInt();
    p.packet.sourcePlugin = plugin->getName();

    QApplication::postEvent(ThreadNetwork::getInstance(), new PluginEvent(p.packet));
}
