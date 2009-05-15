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
    int tmpid;
    tmpid = id;
}

bool Tree::UpdateVector()
{
    qDebug() << "updating vector from database";
    Sql con;
    Tree *tempnode = new Tree();
    QSqlQuery query1("SELECT * FROM treemanagement", QSqlDatabase::database(con));

    maptree.clear();
    while (query1.next())
    {
       tempnode->id = query1.value(0).toInt();

       tempnode->user_ref = query1.value(2).toInt();
       tempnode->parent_id = query1.value(3).toInt();
       maptree.insert(tempnode->id, tempnode);
   }
/*
 for(QMap<int, TreeMngt::node>::const_iterator it = maptree.begin(); it != maptree.end(); ++it)
  {
     QMap<int, TreeMngt::node>::iterator it2 = maptree.find((*it).parent_id);
     if (it2 != maptree.end())
     {
         it2.value().sons.insert(it.value().id, it.value().id);
     }
  }
  */
 //vecshow(vectree);
 return true;
}
