#include "TreeMngt.h"
QMutex TreeMngt::mymute;
QMap<int, TreeMngt::node> TreeMngt::vectree;
TreeMngt::TreeMngt()
{
}

TreeMngt::~TreeMngt()
{
}

bool TreeMngt::DeleteNode(int idnode)
{
    mymute.lock();
    qDebug() << "trying DELETE treemanagement id = "+ QVariant(idnode).toString();

    Sql con;
    QString idparent = "0";
    QSqlQuery query1("SELECT id_parent FROM treemanagement WHERE id = " + QVariant(idnode).toString() + " LIMIT 1", QSqlDatabase::database(con));

    while (query1.next())
    {
        idparent = query1.value(0).toString();
        qDebug() << "id parent = " + idparent;
    }
    if (query1.lastError().isValid())
    {
        qDebug() << "LastError" + query1.lastError().text();
        return false;
    }

    QSqlQuery query2("UPDATE treemanagement SET id_parent = " + idparent +" WHERE id_parent = " + QVariant(idnode).toString(), QSqlDatabase::database(con));

    if (query2.lastError().isValid())
    {
        qDebug() << "DeleteNode() -> Error in refathering new id_parent is weird";
        qDebug() << "LastError" + query2.lastError().text();
        return false;
    }

    QSqlQuery query3("DELETE FROM treemanagement WHERE id = " + QVariant(idnode).toString() + " LIMIT 1", QSqlDatabase::database(con));

    if (query3.lastError().isValid())
    {
        qDebug() << "LastError" + query3.lastError().text();
        return false;
    }
bool ok;
    QMap<int, node>::iterator tmpnode;
    QMap<int, int>::iterator tmpnodesons;
    //virer parent -> fils
    tmpnode = vectree.find(QVariant(idparent).toInt(&ok));
    if (tmpnode != vectree.end())
    {
        tmpnodesons = tmpnode.value().sons.find(idnode);
        if (tmpnodesons != tmpnode.value().sons.end())
            vectree.find(QVariant(idparent).toInt(&ok)).value().sons.remove(idnode);
    }

    //modififier liaison fils -> nouveau parent

    QMap<int, int> tmpsons = GetSonsNode(idnode);

    for(QMap<int, int>::iterator it = tmpsons.begin(); it != tmpsons.end(); ++it)
    {
        tmpnode = vectree.find(it.value());
        if (tmpnode != vectree.end())
        {
            tmpnode.value().parent_id = QVariant(idparent).toInt(&ok);
            tmpnode = vectree.find(QVariant(idparent).toInt(&ok));
            if (tmpnode != vectree.end())
                tmpnode.value().sons.insert(it.value(), it.value());
        }
    }
    //virer idnode
    vectree.remove(idnode);
    mymute.unlock();
        return true;
}

bool TreeMngt::MoveNode(int idmove, int idfather)
{
    qDebug() << "trying MOVE to id_parent = " + QVariant(idfather).toString() +" WHERE id = " + QVariant(idmove).toString();
    Sql con;

    QSqlQuery query2("UPDATE treemanagement SET id_parent = " + QVariant(idfather).toString() +" WHERE id = " + QVariant(idmove).toString(), QSqlDatabase::database(con));

    if (query2.lastError().isValid())
    {
        qDebug() << "MoveNode() -> Error in refathering new id_parent or id is weird";
        qDebug() << "LastError" + query2.lastError().text();
        return false;
    }

    //virer liaison ancien parent -> fils
    QMap<int, TreeMngt::node>::iterator it = vectree.find(vectree.find(idmove).value().parent_id);
    if (it != vectree.end())
    it.value().sons.remove(idmove);
    //modifier liaison fils -> nouveau parent
    vectree.find(idmove).value().parent_id = idfather;
    //ajouter liaison nouveau parent -> fils
    it = vectree.find(idfather);
    it.value().sons.insert(idmove, idmove);
    return true;
}

int TreeMngt::InsertNode(QString name, int userref, int idfather)
{
    qDebug() << "trying INSERT treemanagement name = " + name + " userref = " + QVariant(userref).toString() + " idfather = " + QVariant(idfather).toString();
    Sql con;

    QSqlQuery query("INSERT INTO treemanagement (name, user_ref, id_parent) VALUES ('" + name + "', '" + QVariant(userref).toString() + "', '" + QVariant(idfather).toString() + "')", QSqlDatabase::database(con));

    if (query.lastError().isValid())
    {
        qDebug() << "LastError" + query.lastError().text();
        return false;
    }
    bool ok;
    int id = QVariant(query.lastInsertId()).toInt(&ok);
    qDebug() << "inserted : "<<id;
    node tempnode;
       tempnode.id = id;
       tempnode.name = name;
       tempnode.user_ref = userref;
       tempnode.parent_id = idfather;
       vectree.insert(tempnode.id, tempnode);

    //ajouter liaison nouveau parent -> fils
    QMap<int, TreeMngt::node>::iterator it = vectree.find(idfather);
    if (it != vectree.end())
    {
    //    qDebug() <<  "adding to father " << idfather << " sons :" << id;
     it.value().sons.insert(id, id);
    }
    else
    {
      //  qDebug() << "not found" ;
    }

    vecshow(vectree);
    return true;
}


bool TreeMngt::SetName(int idnode, QString name)
{
    qDebug() << "trying SetName to name = " + name +" WHERE id = " + QVariant(idnode).toString();
       Sql con;

    QSqlQuery query2("UPDATE treemanagement SET name = '" + name +"' WHERE id = " + QVariant(idnode).toString(), QSqlDatabase::database(con));

    if (query2.lastError().isValid())
    {
        qDebug() << "LastError" + query2.lastError().text();
        return false;
    }
    QMap<int, TreeMngt::node>::iterator it = vectree.find(idnode);
    if (it != vectree.end())
    it.value().name = name;
    return true;
}

QString TreeMngt::GetName(int idnode) const
{
    QMap<int, TreeMngt::node>::const_iterator it = vectree.find(idnode);
    if (it != vectree.end())
    return it.value().name;
    else
        return "Not Found !!!";
}


bool TreeMngt::SetUserRef(int idnode, int userref)
{
    qDebug() << "trying SetUserRef to user_ref = " + QVariant(userref).toString() +" WHERE id = " + QVariant(idnode).toString();
       Sql con;

    QSqlQuery query2("UPDATE treemanagement SET user_ref = '" + QVariant(userref).toString() +"' WHERE id = " + QVariant(idnode).toString(), QSqlDatabase::database(con));

    if (query2.lastError().isValid())
    {
        qDebug() << "LastError" + query2.lastError().text();
        return false;
    }
    QMap<int, TreeMngt::node>::iterator it = vectree.find(idnode);
    if (it != vectree.end())
    it.value().user_ref = userref;
    return true;
}

int TreeMngt::GetUserRef(int idnode) const
 {
    QMap<int, TreeMngt::node>::const_iterator it = vectree.find(idnode);
    if (it != vectree.end())
        return it.value().user_ref;
    else
        return 0;
 }

int TreeMngt::GetFatherNode(int idnode) const
{
    QMap<int, TreeMngt::node>::const_iterator it = vectree.find(idnode);
    if (it != vectree.end())
    return it.value().parent_id;
    else
        return 0;
}

QMap<int, int> TreeMngt::GetSonsNode(int idnode) const
{
    QMap<int, TreeMngt::node>::const_iterator it = vectree.find(idnode);
    if (it != vectree.end())
        return it.value().sons;
    else
    {
        QMap<int, int> tmp;
        return tmp;
    }


}


bool TreeMngt::UpdateVector()
{
    qDebug() << "updating vector from database";
    Sql con;
    node tempnode;
    QSqlQuery query1("SELECT * FROM treemanagement", QSqlDatabase::database(con));

 vectree.clear();
    while (query1.next())
    {
       tempnode.id = query1.value(0).toInt();
       tempnode.name = query1.value(1).toString();
       tempnode.user_ref = query1.value(2).toInt();
       tempnode.parent_id = query1.value(3).toInt();
       vectree.insert(tempnode.id, tempnode);
   }

 for(QMap<int, TreeMngt::node>::const_iterator it = vectree.begin(); it != vectree.end(); ++it)
  {
     QMap<int, TreeMngt::node>::iterator it2 = vectree.find((*it).parent_id);
     if (it2 != vectree.end())
     {
         it2.value().sons.insert(it.value().id, it.value().id);
     }
  }
 vecshow(vectree);
 return true;
}

void TreeMngt::vecshow(QMap<int, node> vec)
{
    QString toto = " ";
  for(QMap<int, TreeMngt::node>::const_iterator it = vec.begin(); it != vec.end(); ++it)
  {
    toto = " ";
    for(QMap<int, int>::const_iterator it2 = it.value().sons.begin(); it2 != it.value().sons.end(); ++it2)
    {
         toto += QVariant(*it2).toString() + " -- ";
    }
    qDebug() << QVariant(it.value().id).toString() << " :: " << toto;
  }
}
