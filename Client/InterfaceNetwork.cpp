#include "InterfaceNetwork.h"

#include    <QtGui/QApplication>

#include "ThreadNetwork.h"

#include "../Common/PluginPacket.h"
#include "../Common/CommPlugin.h"

InterfaceNetwork::InterfaceNetwork(IClientPlugin   *plugin)
{
    this->plugin = plugin;
}

void            InterfaceNetwork::sendPacket(const PluginPacket& packet) const
{
    CommPlugin p = packet;

    p.packet.packetVersion = plugin->getVersion().toUInt();
    p.packet.sourcePlugin = plugin->getName();

    QApplication::postEvent(ThreadNetwork::getInstance(), new SendPacketEvent(p.getPacket()));
}
