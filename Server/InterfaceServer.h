#ifndef INTERFACESERVER_H
#define INTERFACESERVER_H

#include "Plugins/IServer.h"
#include "../Common/PluginPacket.h"
#include "Sql.h"

//! Interface given to each plugin to communicate with the server
class InterfaceServer : public IServer
{
public:
    InterfaceServer(IServerPlugin*);

    //! methode to send a packet from a server plugin to a client plugin
    void             sendPacket(const quint32 userId, const PluginPacket& packet) const;
    //! create a Sql and return a SqlQuery instance with this connexion
    QSqlQuery getSqlQuery();
    //! delete the Sql instance
    void freeSql();

    //! return another plugin loaded, return 0 if not found
    IServerPlugin*   getPlugin(const char* name) const;

    //! disconnect Sql connexion if exist
    void cleanInterface();

private:
    //! the only connexion
    Sql* sqlConnexion;
    //! instance of the associated plugin
    IServerPlugin*   plugin;
};

#endif // INTERFACESERVER_H
