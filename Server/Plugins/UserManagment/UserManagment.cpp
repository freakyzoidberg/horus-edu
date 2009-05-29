#include "UserManagment.h"
#include "../../User.h"
#include <QDebug>
#include <QHash>

Q_EXPORT_PLUGIN2(UserManagment, UserManagment)

UserManagment::UserManagment()
{
    requestFunctions["changeMyPassword"] = &UserManagment::changeMyPassword;
    requestFunctions["changeUserPassword"] = &UserManagment::changeUserPassword;
    requestFunctions["createUser"]     = &UserManagment::createUser;
}

void UserManagment::recvPacket(quint32 userId, const PluginPacket& packet)
{
    const QVariantHash request = packet.data.toHash();
    QVariantHash response;

    response["Request"] = request["Request"];
    response["Success"] = false;

    //fill response
    (this->*requestFunctions.value(request["Request"].toByteArray(),//go to the target method
                                   &UserManagment::unknownRequest)) //or if it'sunknown request
                                                                    (userId, request, response);//parameters

    //send response
    server->sendPacket(userId, PluginPacket(packet.sourcePlugin, response));
}

void UserManagment::unknownRequest(quint32 userId, const QVariantHash& request, QVariantHash& response)
{
    response["Success"] = false;
    response["Error"]   = 1;
    response["ErrorMesssage"]   = "Unknow request.";
}

void UserManagment::changeMyPassword(quint32 userId, const QVariantHash& request, QVariantHash& response)
{
    if (! request.contains("OldPassword") || ! request.contains("NewPassword"))
    {
        response["Error"]   = 2;
        response["ErrorMesssage"]   = "Invalid request: You must fill 'OldPassword' and 'NewPassword'";
        return;
    }

    QSqlQuery query = server->getSqlQuery();
    query.prepare("UPDATE users SET password=? WHERE id=? AND password=?;");
    query.addBindValue(request.value("NewPassword").toByteArray().toHex());
    query.addBindValue(userId);
    query.addBindValue(request.value("OldPassword").toByteArray().toHex());
    if ( ! query.exec() || ! query.numRowsAffected() == 1)
    {
        response["Error"]   = 4;
        response["ErrorMesssage"]   = "Passwords doesn't match.";
        return;
    }

    response["Success"] = true;
}

void UserManagment::changeUserPassword(quint32 userId, const QVariantHash& request, QVariantHash& response)
{
    if (User::getUser(userId)->getLevel() > User::ADMINISTRATOR)
    {
        response["Error"]   = 3;
        response["ErrorMesssage"]   = "Permition Denied.";
        return;
    }

    if ( ! request.contains("UserId") || ! request.contains("Password"))
    {
        response["Error"]   = 2;
        response["ErrorMesssage"]   = "Invalid request: You must fill 'UserId' and 'Password'";
        return;
    }

    QSqlQuery query = server->getSqlQuery();
    query.prepare("UPDATE users SET password=? WHERE id=?;");
    query.addBindValue(request.value("Password").toByteArray().toHex());
    query.addBindValue(request.value("UserId"));
    if (query.exec() && query.numRowsAffected() == 1)
    {
        response["Error"]   = 5;
        response["ErrorMesssage"]   = "Invalid UserId " + request["UserId"].toString() + ".";
        return;
    }

    response["Success"] = true;
}

void UserManagment::createUser(quint32 userId, const QVariantHash& request, QVariantHash& response)
{
}
