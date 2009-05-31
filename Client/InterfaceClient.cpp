#include "InterfaceClient.h"

InterfaceClient::InterfaceClient(IClientPlugin *p, ClientApplication *father)
{
    this->parent = father;
    plugin = p;
}

void            InterfaceClient::sendPacket(const PluginPacket& packet) const
{
    CommPlugin p = packet;

    p.packet.packetVersion = plugin->getVersion().toUInt();
    p.packet.sourcePlugin = plugin->getName();

    QApplication::postEvent(ThreadNetwork::getInstance(), new PluginEvent(p.packet));
}

IClientPlugin   *InterfaceClient::getPlugin(const QByteArray name) const
{
    return 0;
}
