#include "Tree.h"
#include <Sql.h>
QHash<int, Tree*> Tree::maptree;

Tree::Tree()
{
}

Tree::~Tree()
{
}

bool     Tree::Delnode()
{
    if (this != 0)
    {
    Sql con;
    QSqlQuery query(QSqlDatabase::database(con));

    for(QHash<int, Tree::Tree*>::iterator it = this->sons.begin(); it != this->sons.end(); ++it)
    {
        query.prepare("UPDATE tree SET id_parent=? WHERE id=?;");

        query.addBindValue(this->parent_id);
        query.addBindValue(it.value()->id);
        if ( ! query.exec())
            {
                qDebug() << query.lastError();
                return false;
            }
        this->parent->sons.insert(it.value()->id, GetNodebyId(it.value()->id));
        it.value()->parent_id = this->parent_id;
        it.value()->parent = this->parent;
        this->sons.remove(it.value()->id);
    }
    query.prepare("DELETE FROM tree WHERE id=?;");
    query.addBindValue(this->id);
        if ( ! query.exec())
            {
                qDebug() << query.lastError();
                return false;
            }

    Tree::maptree.remove(this->id);
    this->sons.clear();
    return true;
    }
    else
    {
        qDebug() << "CRITICAL ERROR   --  Null pointer -- DelNode() method";
        return false;
    }
}


Tree* Tree::GetParent() const
{
    return this->parent;
}

Tree* Tree::GetNodebyId(int id)
{

    QHash<int, Tree::Tree*>::const_iterator it = maptree.find(id);
    if (it != maptree.end())
    {
        return it.value();
    }
    else
    {
        return 0;
    }
}

int Tree::Getid() const
{
    if (this != 0)
    {
        return this->id;
    }
    else
    {
        qDebug() << "CRITICAL ERROR   --  Null pointer -- GetName() method";
        return 0;
    }

}

QString Tree::GetName() const
{
    if (this != 0)
    {
        return this->name;
    }
    else
    {
        qDebug() << "CRITICAL ERROR   --  Null pointer -- GetName() method";
        return "";
    }
}

bool Tree::SetName(QString name)
{
    if (this != 0)
    {
    Sql con;
    QSqlQuery query(QSqlDatabase::database(con));
    query.prepare("UPDATE tree SET name =? WHERE id=?;");
    query.addBindValue(name);
    query.addBindValue(this->id);

    if ( ! query.exec())
        {
            qDebug() << query.lastError();
            return 0;
        }
    this->name = name;
    return true;
    }
    else
    {
        qDebug() << "CRITICAL ERROR   --  Null pointer -- SetName() method";
        return false;
    }
}


QString Tree::GetType() const
{
    if (this != 0)
    {
        return this->type;
    }
    else
    {
        qDebug() << "CRITICAL ERROR   --  Null pointer -- GetType() method";
        return "";
    }
}

bool Tree::SetType(QString type)
{
    if (this != 0)
    {
    Sql con;
    QSqlQuery query(QSqlDatabase::database(con));
    query.prepare("UPDATE tree SET type =? WHERE id=?;");
    query.addBindValue(type);
    query.addBindValue(this->id);

    if ( ! query.exec())
        {
            qDebug() << query.lastError();
            return 0;
        }
    this->type = type;
    return true;
    }
    else
    {
        qDebug() << "CRITICAL ERROR   --  Null pointer -- SetType() method";
        return false;
    }
}

int Tree::GetUserRef() const
{
    if (this != 0)
    {
        return this->user_ref;
    }
    else
    {
        qDebug() << "CRITICAL ERROR   --  Null pointer -- GetUserRef() method";
        return 0;
    }
}

bool Tree::SetUserRef(int user_ref)
{
    if (this != 0)
    {
    Sql con;
    QSqlQuery query(QSqlDatabase::database(con));
    query.prepare("UPDATE tree SET user_ref =? WHERE id=?;");
    query.addBindValue(user_ref);
    query.addBindValue(this->id);

    if ( ! query.exec())
        {
            qDebug() << query.lastError();
            return 0;
        }
    this->name = user_ref;
    return true;
    }
    else
    {
        qDebug() << "CRITICAL ERROR   --  Null pointer -- SetUserRef() method";
        return false;
    }
}



int     Tree::AddSon(int user_ref, QString name, QString type)
{   if (this != 0)
    {
        Sql con;
        QSqlQuery query(QSqlDatabase::database(con));
        query.prepare("INSERT INTO tree (typeofnode,name,user_ref,id_parent) VALUES (?,?,?,?);");

    query.addBindValue(type);
    query.addBindValue(name);
    query.addBindValue(user_ref);
    query.addBindValue(this->id);

    qDebug() << "QUERY:" << query.executedQuery();
        if ( ! query.exec())
        {
            qDebug() << query.lastError();
            return 0;
        }
        Tree *tmpnode = new Tree();
        bool ok;
        tmpnode->id = query.lastInsertId().toInt(&ok);
        tmpnode->name = name;
        tmpnode->parent_id = this->id;
        tmpnode->parent = this;
        tmpnode->user_ref = user_ref;
        this->sons.insert(tmpnode->id, tmpnode);
        maptree.insert(tmpnode->id, tmpnode);
        return tmpnode->id;
    }
    else
    {
        qDebug() << "CRITICAL ERROR   --  Null pointer -- AddSon() method";
        return 0;
    }

}

bool Tree::MoveNode(int idfather)
{
    if ((this != 0) && (Tree::GetNodebyId(idfather) != 0))
    {
    Sql con;
    QSqlQuery query(QSqlDatabase::database(con));
    query.prepare("UPDATE tree SET id_parent =? WHERE id=?;");
    query.addBindValue(idfather);
    query.addBindValue(this->id);

    if ( ! query.exec())
        {
            qDebug() << query.lastError();
            return 0;
        }
    this->parent->sons.remove(this->id);
    this->parent_id = idfather;
    this->parent = Tree::GetNodebyId(idfather);
    this->parent->sons.insert(this->id, this);
    return true;
    }
    else
    {
        qDebug() << "CRITICAL ERROR   --  Null pointer -- MoveNode() method";
        return false;
    }
}

bool Tree::MoveNode(Tree *father)
{
    if ((this != 0) && (father != 0))
    {
    Sql con;
    QSqlQuery query(QSqlDatabase::database(con));
    query.prepare("UPDATE tree SET id_parent =? WHERE id=?;");
    query.addBindValue(father->id);
    query.addBindValue(this->id);

    if ( ! query.exec())
        {
            qDebug() << query.lastError();
            return 0;
        }
    this->parent->sons.remove(this->id);
    this->parent_id = father->id;
    this->parent = father;
    this->parent->sons.insert(this->id, this);
    return true;
    }
    else
    {
        qDebug() << "CRITICAL ERROR   --  Null pointer -- MoveNode() method";
        return false;
    }
}

QHash<int, Tree*> Tree::GetSonsNode() const
{
    if (this != 0)
    {
        return this->sons;
    }
    else
     {
        QHash<int, Tree*> tmp;
        qDebug() << "CRITICAL ERROR   --  Null pointer -- GetSonsNode() method";
        return tmp;
    }
}



bool Tree::UpdateVector()
{
    qDebug() << "=== updating Tree from database ===";
    Sql con;

    QSqlQuery query1("SELECT * FROM tree", QSqlDatabase::database(con));

    maptree.clear();

    Tree *tempnode = new Tree();
       tempnode->id = 0;
       tempnode->user_ref = 0;
       tempnode->name = "/";
       tempnode->type = "group";
       tempnode->parent_id = 0;
        tempnode->parent = tempnode;
       maptree.insert(tempnode->id, tempnode);
    while (query1.next())
    {
       Tree *tempnode = new Tree();
       tempnode->id = query1.value(0).toInt();
       tempnode->type = query1.value(1).toString();
       tempnode->name = query1.value(2).toString();
       tempnode->user_ref = query1.value(3).toInt();
       tempnode->parent_id = query1.value(4).toInt();
       maptree.insert(tempnode->id, tempnode);
   }

 for(QHash<int, Tree::Tree*>::const_iterator it = maptree.begin(); it != maptree.end(); ++it)
  {
     QHash<int, Tree::Tree*>::iterator it2 = maptree.find((*it)->parent_id);
     if (it2 != maptree.end())
     {
         if (it2.value()->id != it.value()->id)
            it2.value()->sons.insert(it.value()->id, it.value());

         it.value()->parent = it2.value();
         qDebug() << "link" << it.value()->id << " to " <<  it2.value()->id;
     }
     else
         qDebug() << "link" << it.value()->id << " is detached !!!";
  }
 qDebug() << "=== Finish updating Tree ===";
 return true;
}

void Tree::ShowSons()
{
    QString listsons = "";
    qDebug() << "---- Show Sons ---- of " << this->id;
    for(QHash<int, Tree::Tree*>::const_iterator it = this->sons.begin(); it != this->sons.end(); ++it)
        listsons += "  --  " + QVariant(it.value()->id).toString();
    listsons += "  --  ";
    qDebug() << listsons;
    qDebug() << "---- End Show Sons ----";
}

void Tree::vecshow()
{
    QString toto = " ";
  for(QHash<int, Tree::Tree*>::const_iterator it = Tree::maptree.begin(); it != Tree::maptree.end(); ++it)
  {
      it.value()->ShowSons();
  }
}

bool Tree::HasFatherId(int fathernode)
{
    Tree *tmpnode = this;

    while ((tmpnode != 0) && (tmpnode->parent_id != 0))
    {
        if (tmpnode->parent_id == fathernode)
            return true;
        else
            tmpnode = tmpnode->parent;
    }
    return false;
}

bool Tree::HasAdminRightOnNodeAndFathers(int userid)
{
    Tree *tmpnode = this;

    while ((tmpnode != 0) && (tmpnode->parent_id != 0))
    {
        if (tmpnode->GetUserRef() == userid)
            return true;
        else
            tmpnode = tmpnode->parent;
    }
    return false;
}
