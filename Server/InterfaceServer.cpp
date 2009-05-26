#include "PluginManager.h"
#include "InterfaceServer.h"
#include "Plugins/IServerPlugin.h"
#include "User.h"
#include "../Common/CommPlugin.h"

InterfaceServer::InterfaceServer(IServerPlugin* p)
{
    plugin = p;
    sqlConnexion = 0;
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

QSqlQuery InterfaceServer::getSqlQuery()
{
    if ( ! sqlConnexion)
        sqlConnexion = new Sql;

    return QSqlQuery(QSqlDatabase::database(*sqlConnexion));
}

void InterfaceServer::freeSql()
{
    if ( ! sqlConnexion)
        return;
    delete sqlConnexion;
    sqlConnexion = 0;
}

void InterfaceServer::cleanInterface()
{
    freeSql();
}
