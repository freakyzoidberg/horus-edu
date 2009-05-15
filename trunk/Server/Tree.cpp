#include "Tree.h"
QMap<int, Tree*> Tree::maptree;
Tree::Tree()
{
}

Tree::~Tree()
{
}

Tree* Tree::GetParent() const
{
    return this->parent;
}

Tree* Tree::GetNodebyId(int id)
{
    QMap<int, Tree::Tree*>::const_iterator it = maptree.find(id);
    if (it != maptree.end())
        return it.value();
    else
    {
        return 0;
    }
}

bool Tree::UpdateVector()
{

    qDebug() << "updating vector from database";
    Sql con;

    QSqlQuery query1("SELECT * FROM treemanagement", QSqlDatabase::database(con));

    maptree.clear();

    Tree *tempnode = new Tree();
       tempnode->id = 0;
       tempnode->user_ref = 0;
       tempnode->name = "/";
        tempnode->type = "group";
       tempnode->parent_id = 0;
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

 for(QMap<int, Tree::Tree*>::const_iterator it = maptree.begin(); it != maptree.end(); ++it)
  {
     QMap<int, Tree::Tree*>::iterator it2 = maptree.find((*it)->parent_id);
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


 //vecshow(vectree);
 return true;
}

void Tree::ShowSons()
{
    qDebug() << "---- Show Sons ---- of " << this->id;
    for(QMap<int, Tree::Tree*>::const_iterator it = this->sons.begin(); it != this->sons.end(); ++it)
        qDebug() << it.value()->id;
    qDebug() << "---- End Show Sons ----";
}
