#include "PluginManager.h"
#include "InterfaceServer.h"
#include "Plugins/IServerPlugin.h"
#include "User.h"

InterfaceServer::InterfaceServer(IServerPlugin* p)
{
    plugin = p;
}

void InterfaceServer::sendPacket(const quint32 userId, const ModulePacket& packet) const
{
    CommModule p = packet;

    p.packet.packetVersion = plugin->version();
    p.packet.sourceModule = plugin->name();

    User* usr = User::getUser(userId);
    if (usr)
    {
        qDebug() << "[out]" << p;
        usr->sendPacket( p.getPacket() );
    }
}

IServerPlugin* InterfaceServer::getPlugin(const char* name) const
{
    return PluginManager::globalInstance()->getPlugin(name);
}
