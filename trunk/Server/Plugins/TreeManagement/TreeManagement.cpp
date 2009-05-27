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
                                                                    (request, response);//parameters

    //send response
    server->sendPacket(userId, PluginPacket(packet.sourcePlugin, response));
}

void  TreeManagement::unknownRequest(const QVariantHash& request,QVariantHash& response)
{

}

void  TreeManagement::gettree(const QVariantHash& request,QVariantHash& response)
{

}

void  TreeManagement::setnode(const QVariantHash& request,QVariantHash& response)
{
}

int TreeManagement::getidofusernode(const QVariantHash &request)
{
    QSqlQuery query1 = server->getSqlQuery();
    query1.prepare("SELECT id_group FROM user_has_group WHERE id_user =?");
    query1.addBindValue("1");
    query1.exec();
    return 1;
}
