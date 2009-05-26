#include "UserManagment.h"
#include <QDebug>
#include <QHash>

Q_EXPORT_PLUGIN2(UserManagment, UserManagment)

UserManagment::UserManagment()
{
    requestFunctions["changePassword"] = &UserManagment::changePassword;
    requestFunctions["createUser"]     = &UserManagment::createUser;
}

void UserManagment::recvPacket(quint32 userId, const PluginPacket& packet)
{
    const QVariantHash request = packet.data.toHash();
    QVariantHash response;

    response["Request"] = request["Request"];

    //fill response
    (this->*requestFunctions.value(request["Request"].toByteArray(),//go to the target method
                                   &UserManagment::unknownRequest)) //or if it'sunknown request
                                                                    (request, response);//parameters

    //send response
    server->sendPacket(userId, PluginPacket(packet.sourcePlugin, response));
}

void UserManagment::unknownRequest(const QVariantHash& request, QVariantHash& response)
{
    response["Success"] = false;
    response["Error"]   = 1;
    response["ErrorMesssage"]   = "Unknow request";
}

void UserManagment::changePassword(const QVariantHash& request, QVariantHash& response)
{
    QSqlQuery query1 = server->getSqlQuery();
    QSqlQuery query2 = server->getSqlQuery();
    QSqlQuery query3 = server->getSqlQuery();
    QSqlQuery query4 = server->getSqlQuery();
    query1.prepare("SELECT id,level FROM users;");
    query2.prepare("SELECT id,level FROM users;");
    query1.exec();
    query1.next();
    query2.exec();
    query2.next();
//    server->freeSql();
}

void UserManagment::createUser(const QVariantHash& request, QVariantHash& response)
{
}
