#ifndef INTERFACESERVER_H
#define INTERFACESERVER_H

#include "Plugins/IServer.h"
#include "../Common/PluginPacket.h"
#include "Sql.h"
#include "Tree.h"

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



    //! retrieve id of node
    Tree::Tree* getnodebyid(qint32 id);
    //! return Tree cached in Server
    QHash<int, Tree*> getTree();
    //! retrieve sons of node
    QHash<int, Tree::Tree*> GetSonsNode(Tree::Tree *tree);
    //! retrieve father of node from son id
    Tree::Tree* getfatherbyid(qint32 id);
    //! retrieve id of node
    int getId(Tree::Tree *tree);

    //! return the level of the connected user
    UserLevel getLevel(quint32 userId) const;


private:
    //! the only connexion
    Sql* sqlConnexion;
    //! instance of the associated plugin
    IServerPlugin*   plugin;
};

#endif // INTERFACESERVER_H
