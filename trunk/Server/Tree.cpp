#include "Tree.h"
QMap<int, Tree*> Tree::maptree;
Tree::Tree()
{
}

Tree::~Tree()
{
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

    while (query1.next())
    {
       Tree *tempnode = new Tree();
       tempnode->id = query1.value(0).toInt();
       tempnode->user_ref = query1.value(2).toInt();
       tempnode->parent_id = query1.value(3).toInt();
       maptree.insert(tempnode->id, tempnode);
   }

 for(QMap<int, Tree::Tree*>::const_iterator it = maptree.begin(); it != maptree.end(); ++it)
  {
     QMap<int, Tree::Tree*>::iterator it2 = maptree.find((*it)->parent_id);
     if (it2 != maptree.end())
     {
         it2.value()->sons.insert(it.value()->id, it.value());
         it.value()->parent = it2.value();
         qDebug() << "link" << it.value()->id << " to " <<  it2.value()->id;
     }
  }


 //vecshow(vectree);
 return true;
}
