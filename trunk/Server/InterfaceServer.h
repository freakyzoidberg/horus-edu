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
    Tree::Tree* getNodenodebyid(qint32 id);
    //! return Tree cached in Server
    QHash<int, Tree*> getNodeTree();
    //! retrieve sons of node
    QHash<int, Tree::Tree*> GetNodeSonsNode(Tree::Tree *tree);
    //! retrieve father of node from son id
    Tree::Tree* getNodefatherbyid(qint32 id);
    //! retrieve id of node
    int getNodeId(Tree::Tree *tree);
    //! retrieve user referee of node
    int getNodeUserRef(Tree::Tree* tree);
    //! retrieve name of node
    QString getNodeName(Tree::Tree* tree);
    //! retrieve type of node
    QString getNodeType(Tree::Tree* tree);
    //! retrieve user referee of node
    bool setNodeUserRef(Tree::Tree* tree, int userref);
    //! retrieve name of node
    bool setNodeName(Tree::Tree* tree, QString name);
    //! retrieve type of node
    bool setNodeType(Tree::Tree* tree, QString type);
    //! check is user has admin right on node
    bool HasNodeAdminRight(Tree::Tree *tree, int userid);
    //! delete node from tree
    bool DelNode(Tree::Tree *node);
    //! move node from tree
    bool MvNode(Tree::Tree *node, int father);
    //! edit node of tree
    int AddNode(Tree::Tree *node, int userref, QString name, QString type);
    //! return the level of the connected user
    UserLevel getLevel(quint32 userId) const;


private:
    //! the only connexion
    Sql* sqlConnexion;
    //! instance of the associated plugin
    IServerPlugin*   plugin;
};

#endif // INTERFACESERVER_H
