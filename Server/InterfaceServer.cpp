#include "PluginManager.h"
#include "InterfaceServer.h"
#include "Plugins/IServerPlugin.h"
#include "User.h"
#include "../Common/CommPlugin.h"

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


bool InterfaceServer::setNodeUserRef(Tree::Tree* tree, int userref)
{
    return tree->SetUserRef(userref);
}

bool InterfaceServer::setNodeName(Tree::Tree* tree, QString name)
{
    return tree->SetName(name);
}

bool InterfaceServer::setNodeType(Tree::Tree* tree, QString type)
{
    return tree->SetType(type);
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
bool InterfaceServer::HasNodeAdminRight(Tree::Tree *tree,int userid)
{
    return tree->HasAdminRightOnNodeAndFathers(userid);
}

bool InterfaceServer::DelNode(Tree::Tree *node)
{
    return node->Delnode();
}

bool InterfaceServer::MvNode(Tree::Tree *node, int father)
{
    return node->MoveNode(father);
}

int InterfaceServer::AddNode(Tree::Tree *node, int userref, QString name, QString type)
{
    return node->AddSon(userref, name, type);
}

QSqlQuery InterfaceServer::getSqlQuery()
{
    if ( ! sqlConnexions.contains(QThread::currentThreadId()))
        sqlConnexions[QThread::currentThreadId()] = new Sql;

    return QSqlQuery(QSqlDatabase::database(*sqlConnexions[QThread::currentThreadId()]));
}

void InterfaceServer::freeSql()
{
    if ( ! sqlConnexions.contains(QThread::currentThreadId()))
        return;
    delete sqlConnexions.value(QThread::currentThreadId());
    sqlConnexions.remove(QThread::currentThreadId());
}

void InterfaceServer::cleanInterface()
{
    freeSql();
}