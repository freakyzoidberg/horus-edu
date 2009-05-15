#include "TreeMngt.h"
QMutex TreeMngt::mymute;
QMap<int, TreeMngt::node> TreeMngt::vectree;
TreeMngt::TreeMngt()
{
}

TreeMngt::~TreeMngt()
{
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
