#include "Tree.h"

#include <QDebug>

QHash<int, Tree*> Tree::maptree;
Tree* Tree::getNodeById(int id)
{
    if ( ! maptree.contains(id))
    {
        Tree* node = new Tree(id);
        node->setObjectName("ITree");
        if (id == 0)
            node->setParent(0);
        maptree[id] = node;
    }

    return maptree[id];
}

void Tree::receiveUserTree(const QVariantList& usertree)
{
    for (QVariantList::const_iterator it = usertree.begin(); it != usertree.end(); ++it)
    {
        QVariantHash elem = (*it).toHash();
        int idNode = elem["id"].toInt();
//        QVariantList list = elem["sons"].toList();
        QVector<ITree*> childs;
//        for (QVariantList::const_iterator it2 = list.begin(); it2 != list.end(); ++it2)
//            childs.append( GetNodebyId( (*it2).toInt() ) );

//        qDebug() << "Tree::receiveUpdate :" << elem["id"] << elem["parentid"] << elem;
        getNodeById(idNode)->receiveUpdate(idNode,
                                           getNodeById(elem["parentid"].toInt()),
                                           elem["userref"].toInt(),
                                           elem["name"].toString(),
                                           elem["type"].toString(),
                                           childs);
    }
    Tree::getNodeById(0)->dumpObjectTree();
}

void Tree::receiveUpdate(const int _id, Tree* _parent, const int _user, const QString _name, const QString _type, const QVector<ITree*> _sons)
{
    id = _id;
    if (_parent != this)
        setParent(_parent);

//    if (_parent != this && ! _parent->findChildren<ITree*>().contains(this))
//        _parent->.append(this);

//    for (QVector<ITree*>::const_iterator i = _sons.begin(); i != _sons.end(); ++i)
//        if ( ! sons.contains(*i))
//            sons.append(*i);

    userId = _user;
    name = _name;
    type = _type;
    loaded = true;

    emit updated();
}

void     Tree::remove()
{
}

void Tree::setName(QString name)
{
}

void Tree::setType(QString type)
{
}

void Tree::setUserId(int user)
{
}

void Tree::createChild(int user_ref, QString name, QString type)
{
}

void Tree::moveTo(int idfather)
{
}

void Tree::moveTo(ITree *father)
{
}

bool Tree::isDescendantOf(int parentId)
{
    for (Tree *tmp = this; tmp != tmp->parent() && tmp; tmp = ((Tree*)tmp->parent()))
        if (tmp->id == parentId)
            return true;
    return false;
}

bool Tree::isDescendantOf(ITree* par)
{
    for (Tree *tmp = this; tmp != tmp->parent() && tmp; tmp = ((Tree*)tmp->parent()))
        if (tmp == par)
            return true;
    return false;
}

bool Tree::canChange()
{
    int userid = 0;//TODO get the current user
    for(Tree *tmp = this; tmp != tmp->parent() && tmp; tmp = ((Tree*)tmp->parent()))
        if (tmp->userId == userid)
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
