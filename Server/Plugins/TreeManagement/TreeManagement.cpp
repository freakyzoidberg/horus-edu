#include "TreeManagement.h"

Q_EXPORT_PLUGIN2(TreeManagement, TreeManagement);

TreeManagement::TreeManagement()
{
    requestFunctions["getTree"] = &TreeManagement::gettree;
    requestFunctions["getAllTree"] = &TreeManagement::getAlltree;
    requestFunctions["getNodeInfo"] = &TreeManagement::getnodeinfo;
    requestFunctions["setNode"] = &TreeManagement::setnode;
    qDebug() << "TreeManagement has arrived";
}

TreeManagement::~TreeManagement()
{
    qDebug() << "bye bye TreeManagement";
}

void TreeManagement::recvPacket(quint32 userId, const PluginPacket& packet)
{
    const QVariantHash request = packet.data.toHash();
    QVariantHash response;

    response["Request"] = request["Request"];

    //fill response
    (this->*requestFunctions.value(request["Request"].toByteArray(),//go to the target method
                                   &TreeManagement::unknownRequest)) //or if it'sunknown request
                                                                    (request, response, userId);//parameters

    //send response
    server->sendPacket(userId, PluginPacket(packet.sourcePlugin, response));
}

void  TreeManagement::unknownRequest(const QVariantHash& request,QVariantHash& response, qint32 iduser)
{
    response["Success"] = false;
    response["Error"]   = 1;
    response["ErrorMesssage"]   = "Unknow request";
}

void  TreeManagement::gettree(const QVariantHash& request,QVariantHash& response, qint32 iduser)
{
    int firstnode = getidofusernode(request, iduser);
    QHash<QString, QVariant > usertree;
    addnodewithsons(&usertree, firstnode);
    addfathers(&usertree,firstnode);
    qDebug() << "=== Tree Management DEBUG ===";
    QList<QVariant> tmplist;
    for (QHash<QString, QVariant >::const_iterator it = usertree.begin(); it != usertree.end(); ++it)
    {
        qDebug() << "User Tree node :" << it.key();
    tmplist = it.value().toList();
       for (int i = 0; i < tmplist.size(); ++i)
        {
          qDebug() << "         sons :" << (tmplist.value(i));
        }
    }
    qDebug() << "=== END Tree Management DEBUG ===";
    response["userTree"] =  usertree;
}

void  TreeManagement::getAlltree(const QVariantHash& request,QVariantHash& response, qint32 iduser)
{
    int firstnode = 0;
    QHash<QString, QVariant > usertree;
    addnodewithsons(&usertree, firstnode);
    addfathers(&usertree,firstnode);
    qDebug() << "=== Tree Management DEBUG ===";
    QList<QVariant> tmplist;
    for (QHash<QString, QVariant >::const_iterator it = usertree.begin(); it != usertree.end(); ++it)
    {
        qDebug() << "User Tree node :" << it.key();
    tmplist = it.value().toList();
       for (int i = 0; i < tmplist.size(); ++i)
        {
          qDebug() << "         sons :" << (tmplist.value(i));
        }
    }
    qDebug() << "=== END Tree Management DEBUG ===";
    response["AllTree"] =  usertree;


}

void  TreeManagement::getnodeinfo(const QVariantHash& request,QVariantHash& response, qint32 iduser)
{
    bool ok;
    int node = QVariant(request["idNode"]).toInt(&ok);

    response["userref"] = server->getnodebyid(node)->user_ref;
    response["nodename"] =  server->getnodebyid(node)->name;
    response["numberofsons"] = server->GetSonsNode(server->getnodebyid(node)).count();
    response["sonsid"] = getvectorsonsfromidnode(node);
}



void  TreeManagement::setnode(const QVariantHash& request,QVariantHash& response, qint32 iduser)
{
    bool ok;
    if (request["Admntreeact"] == "Delnode")
    {
       if (delnode(request["Id"].toInt(&ok)))
           response["Success"] = true;
         else
        {
            response["Error"] = 1;
            response["ErrorMessage"] = "cannot delete this node";
         }
         return;
    }
    else if (request["Admntreeact"] == "Mvnode")
    {
        if (mvnode(request["id"].toInt(&ok), request["Newfathe"].toInt(&ok)))    
            response["Success"] = true;
        else
        {
            response["Error"] = 1;
            response["ErrorMessage"] = "cannot move this node";
         }
        return;
    }
    else if (request["Admntreeact"] == "Addnode")
    {
        if (addnode(request["Newfather"].toInt(&ok), request["Type"], request["Name"], request["UserRef"].toInt(&ok)))
            response["Success"] = true;
        else
        {
            response["Error"] = 1;
            response["ErrorMessage"] = "cannot add this node";
         }
        return;
    }
    else if (request["Admntreeact"] == "Setnode")
    {
        if (setnode(request["Id"].toInt(&ok), request["Type"], request["Name"], request["UserRef"].toInt(&ok)))
            response["Success"] = true;
        else
        {
            response["Error"] = 1;
            response["ErrorMessage"] = "cannot set this node";
         }
        return;
    }
    response["Error"] = 1;
    response["ErrorMessage"] = "request not handled";
    return;
}


bool  TreeManagement::delnode(const int id)
{
    return (server->getnodebyid(id)->Delnode());
}

bool  mvnode(const int id, const int newfatherid)
{
    return (server->getnodebyid(id)->MoveNode(newfatherid));
}

bool  addnode(const int fatherid, const QString type, const QString name, const int user_ref)
{
   if (server->getnodebyid(fatherid)->AddSon(user_ref, name, type) != 0)
      return true;
   else
       return false;
}

bool  setnode(const int nodeid, const QString type, const QString name, const int user_ref)
{
    bool res = true;
    Tree* node =server->getnodebyid(nodeid);
    if (node->GetName() != name)
        res = ((res == false) ? false :(node->SetName(name) == false) ? false : true);
    if (node->GetUserRef() != user_ref)
        res = ((res == false) ? false :(node->SetUserRef(user_ref) == false) ? false : true);
    if (node->GetType() != type)
        res = ((res == false) ? false :(node->SetType(type) == false) ? false : true);
    return res;
}

int TreeManagement::getidofusernode(const QVariantHash& request, qint32 iduser)
{
    QSqlQuery query1 = server->getSqlQuery();
    query1.prepare("SELECT id_group FROM user_has_group WHERE id_user =? LIMIT 1");
    query1.addBindValue(iduser);
    query1.exec();

    bool ok;
    while (query1.next())
    {
        return query1.value(0).toInt(&ok);
    }
    return 0;
}

int TreeManagement::getidofusernodeWoRequest(qint32 iduser)
{
    QSqlQuery query1 = server->getSqlQuery();
    query1.prepare("SELECT id_group FROM user_has_group WHERE id_user =? LIMIT 1");
    query1.addBindValue(iduser);
    query1.exec();

    bool ok;
    while (query1.next())
    {
        return query1.value(0).toInt(&ok);
    }
    return 0;
}

QList<QVariant> TreeManagement::getvectorsonsfromidnode(int idnode)
{
    QList<QVariant> sons;

    sons.clear();
    QHash<int, Tree::Tree*> nodesons = server->GetSonsNode(server->getnodebyid(idnode));

    for(QHash<int, Tree::Tree*>::iterator it = nodesons.begin(); it != nodesons.end(); ++it)
    {
       sons.append(QVariant(server->getId(it.value())));
     }
    return sons;
}
void  TreeManagement::addnodewithsons(QHash<QString, QVariant > *utree, int id)
{
    QList<QVariant> tmpvec = getvectorsonsfromidnode(id);

   utree->insert(QVariant(server->getId(server->getnodebyid(id))).toString(), tmpvec);
   bool ok;
    for (QList<QVariant>::const_iterator it = tmpvec.begin(); it != tmpvec.end(); ++it)
    {
        addnodewithsons(utree, QVariant(*it).toInt(&ok));
    }

}

void  TreeManagement::addfathers(QHash<QString, QVariant > *utree,const int id)
{

    if ((server->getfatherbyid(id) != 0))
    {
         QVariant tmpvec;

        tmpvec.toList().append(QVariant(id));
        utree->insert(QVariant(server->getId(server->getfatherbyid(id))).toString(), tmpvec);
        if ((server->getId(server->getfatherbyid(id)) != 0))
           addfathers(utree, server->getId(server->getfatherbyid(id)));
    }

}

QList<int> TreeManagement::GetNodeList(int iduser)
{
    QList<int> listret;
    listret.clear();
    int firstnode = getidofusernodeWoRequest(iduser);
    QHash<QString, QVariant > usertree;
    addnodewithsons(&usertree, firstnode);
    addfathers(&usertree,firstnode);
    bool ok;
     for (QHash<QString, QVariant >::const_iterator it = usertree.begin(); it != usertree.end(); ++it)
    {
        listret.append(QVariant(it.key()).toInt(&ok));
    }
return listret;
}
