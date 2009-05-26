#include "PluginManager.h"
#include "InterfaceServer.h"
#include "Plugins/IServerPlugin.h"
#include "User.h"
#include "../Common/CommPlugin.h"
#include "Sql.h"

InterfaceServer::InterfaceServer(IServerPlugin* p)
{
    plugin = p;
}

void InterfaceServer::sendPacket(const quint32 userId, const PluginPacket& packet) const
{
    CommPlugin p = packet;

    p.packet.packetVersion = plugin->version();
    p.packet.sourcePlugin = plugin->name();

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

QByteArray* InterfaceServer::GetSql() const
{
    return new Sql();
}
