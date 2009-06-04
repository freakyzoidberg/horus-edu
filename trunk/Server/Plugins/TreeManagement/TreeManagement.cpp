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
    response["Success"] = true;
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
    response["Success"] = true;

}

void  TreeManagement::getnodeinfo(const QVariantHash& request,QVariantHash& response, qint32 iduser)
{
    bool ok;
    if (request.contains("idNode"))
    {
    int node = QVariant(request["idNode"]).toInt(&ok);

      response["userref"] = server->getNodeUserRef(server->getNodenodebyid(node));
      response["nodename"] =  server->getNodeName(server->getNodenodebyid(node));
      response["numberofsons"] = server->GetNodeSonsNode(server->getNodenodebyid(node)).count();
      response["sonsid"] = getvectorsonsfromidnode(node);
      response["userslist"] = userlist(node);
      response["type"] = server->getNodeType(server->getNodenodebyid(node));
      response["Success"] = true;
    }
    else
    {
        response["Success"] = false;
        response["Error"]   = 1;
        response["ErrorMesssage"]   = "no id specified";
    }
}



void  TreeManagement::setnode(const QVariantHash& request,QVariantHash& response, qint32 iduser)
{
    bool ok;
    if (request["Admntreeact"] == "Delnode")
    {
       if (delnode(request["Id"].toInt(&ok), iduser))
           response["Success"] = true;
         else
        {
             response["Success"] = false;
            response["Error"] = 1;
            response["ErrorMessage"] = "cannot delete this node";
         }
         return;
    }
    else if (request["Admntreeact"] == "Mvnode")
    {
        if (mvnode(request["Id"].toInt(&ok), request["Newfather"].toInt(&ok), iduser))
            response["Success"] = true;
        else
        {
            response["Success"] = false;
            response["Error"] = 1;
            response["ErrorMessage"] = "cannot move this node";
         }
        return;
    }
    else if (request["Admntreeact"] == "Addnode")
    {
        if (addnode(request["Newfather"].toInt(&ok), request["Type"].toString(), request["Name"].toString(), request["UserRef"].toInt(&ok), iduser))
            response["Success"] = true;
        else
        {
            response["Success"] = false;
            response["Error"] = 1;
            response["ErrorMessage"] = "cannot add this node";
         }
        return;
    }
    else if (request["Admntreeact"] == "Setnode")
    {
        if (editnode(request["Id"].toInt(&ok), request["Type"].toString(), request["Name"].toString(), request["UserRef"].toInt(&ok), iduser))
            response["Success"] = true;
        else
        {
            response["Success"] = false;
            response["Error"] = 1;
            response["ErrorMessage"] = "cannot set this node";
         }
        return;
    }
    response["Success"] = false;
    response["Error"] = 1;
    response["ErrorMessage"] = "request not handled";
    return;
}


bool  TreeManagement::delnode(const int id, const int iduser)
{
    Tree * node = server->getNodenodebyid(id);
    if (server->HasNodeAdminRight(node, iduser))
        return (server->DelNode(node));
    else
        return false;
}

bool  TreeManagement::mvnode(const int id, const int newfatherid, const int iduser)
{
    Tree * node = server->getNodenodebyid(id);
    if (server->HasNodeAdminRight(node, iduser))
    return (server->MvNode(node, newfatherid));
    else
        return false;
}

bool  TreeManagement::addnode(const int fatherid, const QString type, const QString name, const int user_ref, const int iduser)
{
    Tree * node = server->getNodenodebyid(fatherid);
    if (server->HasNodeAdminRight(node, iduser))
    {
      if (server->AddNode(node,user_ref, name, type) != 0)
       return true;
     else
       return false;
    }
    else
        return false;
}

bool  TreeManagement::editnode(const int nodeid, const QString type, const QString name, const int user_ref, const int iduser)
{
    bool res = true;
     Tree * node = server->getNodenodebyid(nodeid);
    if (server->HasNodeAdminRight(node, iduser))
    {
    if (server->getNodeName(node) != name)
        res = ((res == false) ? false : (server->setNodeName(node, name) == false) ? false : true);
    if (server->getNodeUserRef(node) != user_ref)
        res = ((res == false) ? false :(server->setNodeUserRef(node,user_ref) == false) ? false : true);
    if (server->getNodeType(node) != type)
        res = ((res == false) ? false :(server->setNodeType(node, type) == false) ? false : true);
    return res;
    }
    return false;
}

int TreeManagement::getidofusernode(const QVariantHash& request, qint32 iduser)
{
    QSqlQuery query1 = server->getSqlQuery();
    query1.prepare("SELECT id_tree FROM users WHERE id =? LIMIT 1");
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
    query1.prepare("SELECT id_tree FROM users WHERE id =? LIMIT 1");
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
    QHash<int, Tree::Tree*> nodesons = server->GetNodeSonsNode(server->getNodenodebyid(idnode));

    for(QHash<int, Tree::Tree*>::iterator it = nodesons.begin(); it != nodesons.end(); ++it)
    {
       sons.append(QVariant(server->getNodeId(it.value())));
     }
    return sons;
}
void  TreeManagement::addnodewithsons(QHash<QString, QVariant > *utree, int id)
{
    QList<QVariant> tmpvec = getvectorsonsfromidnode(id);

   utree->insert(QVariant(server->getNodeId(server->getNodenodebyid(id))).toString(), tmpvec);
   bool ok;
    for (QList<QVariant>::const_iterator it = tmpvec.begin(); it != tmpvec.end(); ++it)
    {
        addnodewithsons(utree, QVariant(*it).toInt(&ok));
    }

}

void  TreeManagement::addfathers(QHash<QString, QVariant > *utree,const int id)
{

    if ((server->getNodefatherbyid(id) != 0))
    {
         QVariant tmpvec;

        tmpvec.toList().append(QVariant(id));
        utree->insert(QVariant(server->getNodeId(server->getNodefatherbyid(id))).toString(), tmpvec);
        if ((server->getNodeId(server->getNodefatherbyid(id)) != 0))
           addfathers(utree, server->getNodeId(server->getNodefatherbyid(id)));
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

QList<QVariant> TreeManagement::userlist(const int id_node)
{
    QList<QVariant> res;
    QSqlQuery query1 = server->getSqlQuery();
    query1.prepare("SELECT id FROM users WHERE id_tree =?");
    query1.addBindValue(id_node);
    query1.exec();

    bool ok;
    res.clear();
    while (query1.next())
    {
        res.append(query1.value(0).toInt(&ok));
    }
    return res;
}
