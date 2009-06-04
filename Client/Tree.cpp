#include "Tree.h"

#include <QApplication>

#include "../Common/CommPlugin.h"
#include "ThreadNetwork.h"


QHash<int, Tree*> Tree::maptree;
Tree* Tree::GetNodebyId(int id)
{
    QHash<int,Tree*>::const_iterator it = maptree.find(id);
    if (it != maptree.end())
        return *it;

    return new Tree(id);
}

void Tree::updateUserTree()
{
    QVariantHash request;
    request["Request"] = "getTree+";

    PluginPacket req("TreeManagement", request);
    req.sourcePlugin = "TreeManagement";
    req.packetVersion = 0;

    QApplication::postEvent(ThreadNetwork::getInstance(), new SendPacketEvent(CommPlugin(req).getPacket()));
}

void Tree::receiveUserTree(const QVariantHash& response)
{
    if ( ! response["Success"].toBool())
        return;

    QVariantHash usertree = response["userTree"].toHash();
    for (QVariantHash::const_iterator it = usertree.begin(); it != usertree.end(); ++it)
    {
        QVariantHash elem = (*it).toHash();
        int idNode = it.key().toInt();
        QVariantList list = elem["sons"].toList();
        QHash<int,Tree*> sons;
        for (QVariantList::const_iterator it2 = list.begin(); it2 != list.end(); ++it2)
        {
            int idSon = (*it2).toInt();
            sons[ idSon ] = GetNodebyId(idSon);
        }
        GetNodebyId(idNode)->receiveUpdate(idNode,
                                           elem["parentId"].toInt(),
                                           elem["userref"].toInt(),
                                           elem["name"].toString(),
                                           elem["type"].toString(),
                                           sons);
    }
}

void Tree::receiveUpdate(const int _id, const int _parent, const int _user_ref, const QString _name, const QString _type, const QHash<int,Tree*> _sons)
{
    id = _id;
    parent = GetNodebyId(_parent);
    user_ref = _user_ref;
    name = _name;
    type = _type;
    sons = _sons;

   qDebug() << "Tree::receiveUpdate :" << id << parent << user_ref << name << type << sons;

   emit nodeUpdated();
}

void     Tree::Delnode()
{
}

void Tree::SetName(QString name)
{
}

void Tree::SetType(QString type)
{
}

void Tree::SetUserRef(int user_ref)
{
}

void Tree::AddSon(int user_ref, QString name, QString type)
{
}

void Tree::MoveNode(int idfather)
{
}

void Tree::MoveNode(Tree *father)
{
}

bool Tree::HasFatherId(int fathernode)
{
    for (Tree *tmpnode = this; tmpnode->Getid() && tmpnode->parent; tmpnode = tmpnode->parent)
        if (tmpnode->parent->Getid() == fathernode)
            return true;
    return false;
}

bool Tree::HasAdminRightOnNodeOrFathers(int userid)
{
    for(Tree *tmpnode = this; tmpnode->Getid() && tmpnode->parent; tmpnode = tmpnode->parent)
        if (tmpnode->GetUserRef() == userid)
            return true;

    return false;
}

//
//bool Tree::UpdateVector()
//{
//    qDebug() << "=== updating Tree from database ===";
//    Sql con;
//
//    QSqlQuery query1("SELECT * FROM tree", QSqlDatabase::database(con));
//
//    maptree.clear();
//
//    Tree *tempnode = new Tree();
//       tempnode->id = 0;
//       tempnode->user_ref = 0;
//       tempnode->name = "/";
//       tempnode->type = "group";
//       tempnode->parent_id = 0;
//       maptree.insert(tempnode->id, tempnode);
//    while (query1.next())
//    {
//       Tree *tempnode = new Tree();
//       tempnode->id = query1.value(0).toInt();
//       tempnode->type = query1.value(1).toString();
//       tempnode->name = query1.value(2).toString();
//       tempnode->user_ref = query1.value(3).toInt();
//       tempnode->parent_id = query1.value(4).toInt();
//       maptree.insert(tempnode->id, tempnode);
//   }
//
// for(QHash<int, Tree::Tree*>::const_iterator it = maptree.begin(); it != maptree.end(); ++it)
//  {
//     QHash<int, Tree::Tree*>::iterator it2 = maptree.find((*it)->parent_id);
//     if (it2 != maptree.end())
//     {
//         if (it2.value()->id != it.value()->id)
//            it2.value()->sons.insert(it.value()->id, it.value());
//
//         it.value()->parent = it2.value();
//         qDebug() << "link" << it.value()->id << " to " <<  it2.value()->id;
//     }
//     else
//         qDebug() << "link" << it.value()->id << " is detached !!!";
//  }
// qDebug() << "=== Finish updating Tree ===";
// return true;
//}
//
//void Tree::ShowSons()
//{
//    QString listsons = "";
//    qDebug() << "---- Show Sons ---- of " << this->id;
//    for(QHash<int, Tree::Tree*>::const_iterator it = this->sons.begin(); it != this->sons.end(); ++it)
//        listsons += "  --  " + QVariant(it.value()->id).toString();
//    listsons += "  --  ";
//    qDebug() << listsons;
//    qDebug() << "---- End Show Sons ----";
//}
//
//void Tree::vecshow()
//{
//    QString toto = " ";
//    for(QHash<int, Tree::Tree*>::const_iterator it = Tree::maptree.begin(); it != Tree::maptree.end(); ++it)
//        it.value()->ShowSons();
//}
