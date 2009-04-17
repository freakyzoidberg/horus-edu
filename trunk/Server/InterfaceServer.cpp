#include "PluginManager.h"
#include "InterfaceServer.h"
#include "Plugins/IServerPlugin.h"
#include "User.h"

void InterfaceServer::sendPacket(const quint32 userId, const ModulePacket& packet) const
{
    CommModule p = packet;
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
