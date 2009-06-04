#ifndef ISERVER_H
#define ISERVER_H

#include <QByteArray>
#include <QtSql>
#include "../../Common/PluginPacket.h"
#include "../Tree.h"
#include "../../Common/Defines.h"


class IServerPlugin;

//! Interface given to each plugin to communicate with the server
class IServer
{
public:
    //! methode to send a packet from a server plugin to a client plugin
    virtual void           sendPacket(const quint32 userId, const PluginPacket& packet) const = 0;
    //! create a Sql and return a SqlQuery instance with this connexion
    virtual QSqlQuery getSqlQuery() = 0;
    //! delete a Sql instance
    virtual void freeSql() = 0;
    //! return another plugin loaded, return 0 if not found
    virtual IServerPlugin* getPlugin(const char* name) const = 0;
    //! return the level of the connected user
    virtual UserLevel getLevel(quint32 userId) const = 0;

    // Should be in independant interface ?

    //! retrieve the tree for a plugin
    virtual QHash<int, Tree::Tree*> getNodeTree() = 0;
    //! retrieve node by id
    virtual Tree::Tree* getNodenodebyid(qint32 id) = 0;
    //! retrieve father of node from son id
    virtual Tree::Tree* getNodefatherbyid(qint32 id) = 0;
    //! retrieve id of node
    virtual int getNodeId(Tree::Tree* tree) = 0;
    //! retrieve user referee of node
    virtual int getNodeUserRef(Tree::Tree* tree) = 0;
    //! retrieve name of node
    virtual QString getNodeName(Tree::Tree* tree) = 0;
    //! retrieve type of node
    virtual QString getNodeType(Tree::Tree* tree) = 0;
    //! retrieve user referee of node
    virtual void setNodeUserRef(Tree::Tree* tree, int userref) = 0;
    //! retrieve name of node
    virtual void setNodeName(Tree::Tree* tree, QString name) = 0;
    //! retrieve type of node
    virtual void setNodeType(Tree::Tree* tree, QString type) = 0;
    //! retrieve sons of node
    virtual QHash<int, Tree::Tree*> GetNodeSonsNode(Tree::Tree *tree) = 0;
};

#endif // ISERVER_H
