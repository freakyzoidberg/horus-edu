#include "TreeManagement.h"

Q_EXPORT_PLUGIN2(TreeManagement, TreeManagement);

TreeManagement::TreeManagement()
{
    requestFunctions["getTree"] = &TreeManagement::gettree;
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
    for (QHash<QString, QVariant >::const_iterator it = usertree.begin(); it != usertree.end(); ++it)
    {
        qDebug() << "User Tree node :" << it.key();

       for (int i = 0; i < it.value().toList().size(); ++i)
        {
          qDebug() << "         sons :" << (it.value().toList().value(i));
        }
    }
    qDebug() << "=== END Tree Management DEBUG ===";
    //response["tree"] =  usertree;
}

void  TreeManagement::setnode(const QVariantHash& request,QVariantHash& response, qint32 iduser)
{
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

QList<QVariant> TreeManagement::getvectorsonsfromidnode(int idnode)
{
    QList<QVariant> sons;

    sons.clear();

    QHash<int, Tree::Tree*> nodesons = server->GetSonsNode(server->getnodebyid(idnode));

    //qDebug() << nodesons;
    for(QHash<int, Tree::Tree*>::iterator it = nodesons.begin(); it != nodesons.end(); ++it)
    {
        qDebug() << "kk " << server->getId(it.value());
       sons.append(QVariant(server->getId(it.value())));
     }
    return sons;
}
void  TreeManagement::addnodewithsons(QHash<QString, QVariant > *utree, int id)
{

    //QVariant tmpvec = QVariant(getvectorsonsfromidnode(id));
    QList<QVariant> tmpvec = getvectorsonsfromidnode(id);
//    qDebug() << "tmpvec direct 0 " << tmpvec[0];


   utree->insert(QVariant(server->getId(server->getnodebyid(id))).toString(), tmpvec);
   bool ok;
    for (QList<QVariant>::const_iterator it = tmpvec.begin(); it != tmpvec.end(); ++it)
    {
        ok = NULL;

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
