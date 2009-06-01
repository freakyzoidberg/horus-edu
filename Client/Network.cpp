#include    <QtGui/QApplication>

#include "ThreadNetwork.h"
#include "NetworkSender.h"
#include "../Common/PluginPacket.h"
#include "../Common/CommPlugin.h"

NetworkSender::NetworkSender()
{
}

void            NetworkSender::sendPacket(const PluginPacket& packet) const
{
    CommPlugin p = packet;

    p.packet.packetVersion = plugin->getVersion().toUInt();
    p.packet.sourcePlugin = plugin->getName();

    QApplication::postEvent(ThreadNetwork::getInstance(), new PluginEvent(p.packet));
}
