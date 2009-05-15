#include "TreeMngt.h"
QMutex TreeMngt::mymute;
QMap<int, TreeMngt::node> TreeMngt::vectree;
TreeMngt::TreeMngt()
{
}

TreeMngt::~TreeMngt()
{
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
