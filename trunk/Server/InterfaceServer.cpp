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

UserLevel InterfaceServer::getLevel(quint32 userId) const
{
    return User::getUser(userId)->getLevel();
}

int InterfaceServer::getNodeId(Tree::Tree* tree)
{
    return tree->Getid();
}

int InterfaceServer::getNodeUserRef(Tree::Tree* tree)
{
    return tree->GetUserRef();
}

QString InterfaceServer::getNodeName(Tree::Tree* tree)
{
    return tree->GetName();
}

QString InterfaceServer::getNodeType(Tree::Tree* tree)
{
    return tree->GetType();
}


void InterfaceServer::setNodeUserRef(Tree::Tree* tree, int userref)
{
    tree->SetUserRef(userref);
}

void InterfaceServer::setNodeName(Tree::Tree* tree, QString name)
{
    tree->SetName(name);
}

void InterfaceServer::setNodeType(Tree::Tree* tree, QString type)
{
    tree->SetType(type);
}

QHash<int, Tree::Tree*> InterfaceServer::GetNodeSonsNode(Tree::Tree* tree)
{

    return tree->GetSonsNode();
}

Tree::Tree* InterfaceServer::getNodefatherbyid(qint32 id)
{
    return Tree::GetNodebyId(id)->GetParent();
}
Tree::Tree* InterfaceServer::getNodenodebyid(qint32 id)
{
    return Tree::GetNodebyId(id);
}
QHash<int, Tree*> InterfaceServer::getNodeTree()
{
    return Tree::maptree;
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
