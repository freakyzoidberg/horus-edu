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
    QHash<int, QVector<int> > usertree;

    usertree.insert(server->getId(server->getnodebyid(firstnode)), getvectorsonsfromidnode(firstnode));
     // server->getTree().value(firstnode);
}

void  TreeManagement::setnode(const QVariantHash& request,QVariantHash& response, qint32 iduser)
{
}

int TreeManagement::getidofusernode(const QVariantHash &request, qint32 iduser)
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

QVector<int> TreeManagement::getvectorsonsfromidnode(qint32 idnode)
{
    QVector<int> sons;
    sons.clear();
    for(QHash<int, Tree::Tree*>::const_iterator it = server->GetSonsNode(server->getnodebyid(idnode)).begin(); it != server->GetSonsNode(server->getnodebyid(idnode)).end(); ++it)
    {
        sons.append(it.value()->Getid());
     }
    return sons;
}
