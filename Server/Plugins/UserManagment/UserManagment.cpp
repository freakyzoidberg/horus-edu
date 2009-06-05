#include "UserManagment.h"
#include <QDebug>
#include <QHash>

Q_EXPORT_PLUGIN2(UserManagment, UserManagment)

UserManagment::UserManagment()
{
    requestFunctions["changePassword"] = &UserManagment::changePassword;
    requestFunctions["listUsers"]    = &UserManagment::listUsers;
    requestFunctions["getUserInfo"]    = &UserManagment::getUserInfo;
    requestFunctions["setUserInfo"]    = &UserManagment::setUserInfo;
    requestFunctions["createNewUser"]  = &UserManagment::createNewUser;
    requestFunctions["disableUser"]    = &UserManagment::disableUser;
}

void UserManagment::recvPacket(quint32 userId, const PluginPacket& packet)
{
    QVariantHash request = packet.data.toHash();
    QVariantHash response;

    response["Request"] = request["Request"];
    response["Success"] = false;

    if ( ! request.contains("UserId"))
        request["UserId"] = userId;

    if (request["UserId"].toUInt() != userId && server->getLevel(userId) > LEVEL_ADMINISTRATOR)
    {
        response["Success"] = false;
        response["Error"]   = 3;
        response["ErrorMesssage"]   = "Permition denied.";
    }

    response["UserId"] = request["UserId"];

    //fill response
    (this->*requestFunctions.value(request["Request"].toByteArray(),//go to the target method
                                   &UserManagment::unknownRequest)) //or if it'sunknown request
                                                                    (userId, request, response);//parameters

    //send response
    server->sendPacket(userId, PluginPacket(packet.sourcePlugin, response));
}

void UserManagment::unknownRequest(quint32, const QVariantHash&, QVariantHash& response)
{
    response["Success"] = false;
    response["Error"]   = 1;
    response["ErrorMesssage"]   = "Unknow request.";
}

void UserManagment::changePassword(quint32 userId, const QVariantHash& request, QVariantHash& response)
{
    if ( ! request.contains("password"))
    {
        response["Error"]   = 2;
        response["ErrorMesssage"]   = "Invalid request: You must fill 'password'";
        return;
    }

    QSqlQuery query = server->getSqlQuery();
    if (request.contains("OldPassword"))
    {
        query.prepare("UPDATE users SET password=? WHERE password=? AND id=?;");
        query.addBindValue(request["password"].toByteArray().toHex());
        query.addBindValue(request["OldPassword"].toByteArray().toHex());
    }
    else if (server->getLevel(userId) > LEVEL_ADMINISTRATOR)
    {
        query.prepare("UPDATE users SET password=? WHERE id=?;");
        query.addBindValue(request["password"].toByteArray().toHex());
    }
    else
    {
        response["Error"]   = 2;
        response["ErrorMesssage"]   = "Invalid request: You must fill 'OldPassword'";
        return;
    }

    query.addBindValue(request["UserId"]);
    if ( ! query.exec() || ! query.numRowsAffected() == 1)
    {
        response["Error"]   = 4;
        response["ErrorMesssage"]   = "Passwords doesn't match.";
        return;
    }

    response["Success"] = true;
}

void UserManagment::listUsers(quint32 userId, const QVariantHash& request,QVariantHash& response)
{
    QSqlQuery query = server->getSqlQuery();
    if (request.contains("UserList"))
    {
        QVariantList list = request["UserList"].toList();
        QString sql = "SELECT id,login,level,last_login,surname,name,birth_date,picture,address,phone,country,language,id_tree,enabled FROM users WHERE id IN (0";
        for (QVariantList::const_iterator i = list.constBegin(); i != list.constEnd(); ++i)
            list += "," + (*i).toUInt();
        query.prepare(sql+");");
    }
    else
        query.prepare("SELECT id,login,level,last_login,surname,name,birth_date,picture,address,phone,country,language,id_tree,enabled FROM users;");

    if ( ! query.exec())
    {
        response["Error"]   = 6;
        response["ErrorMesssage"] = "Database error.";
        return;
    }

    response["Success"] = true;
    QVariantList list;
    while (query.next())
    {
        QVariantHash user;
        user["id"]         = query.value(0);
        user["login"]      = query.value(1);
        user["id_tree"]    = query.value(8);

        if (server->getLevel(userId) <= LEVEL_ADMINISTRATOR || query.value(0).toUInt() == userId)
        {
            user["level"]      = query.value(2);
            user["last_login"] = query.value(3);
            user["surname"]    = query.value(4);
            user["name"]       = query.value(5);
            user["birth_date"] = query.value(6);
            user["picture"]    = query.value(7);
            user["address"]    = query.value(8);
            user["phone"]      = query.value(9);
            user["country"]    = query.value(10);
            user["language"]   = query.value(11);
            user["enabled"]    = query.value(12);
        }
        list.append(user);
    }
    response["Users"] = list;
}

void UserManagment::getUserInfo(quint32, const QVariantHash& request,QVariantHash& response)
{
    QSqlQuery query = server->getSqlQuery();
    query.prepare("SELECT login,level,last_login,surname,name,birth_date,picture,address,phone,country,language,id_tree,enabled FROM users WHERE id=?;");
    query.addBindValue(request.value("UserId"));
    if ( ! query.exec() || ! query.next())
    {
        response["Error"]   = 5;
        response["ErrorMesssage"] = "UserId " + request["UserId"].toString() + " not found.";
        return;
    }

    response["Success"]    = true;

    response["login"]      = query.value(0);
    response["level"]      = query.value(1);
    response["last_login"] = query.value(2);
    response["surname"]    = query.value(3);
    response["name"]       = query.value(4);
    response["birth_date"] = query.value(5);
    response["picture"]    = query.value(6);
    response["address"]    = query.value(7);
    response["phone"]      = query.value(8);
    response["country"]    = query.value(9);
    response["language"]   = query.value(10);
    response["id_tree"]    = query.value(11);
    response["enabled"]    = query.value(12);
}

void UserManagment::setUserInfo(quint32 userId, const QVariantHash& request,QVariantHash& response)
{
    if ( ! request.contains("level") ||  ! request.contains("address") ||  ! request.contains("phone")
      || ! request.contains("country") || ! request.contains("language") || ! request.contains("id_tree")
      || ! request.contains("surname") || ! request.contains("name") || ! request.contains("birth_date")
      || ! request.contains("picture") || ! request.contains("enabled"))
    {
        response["Error"]   = 2;
        response["ErrorMesssage"]   = "Invalid request: You must fill 'level','address','phone','counrty','language','id_tree','enabled','surname','name','birth_date','picture'";
        return;
    }

    if (request["level"].toInt() < server->getLevel(userId))
    {
        response["Error"]   = 3;
        response["ErrorMesssage"]   = "Permition denied: You can't give more privileges than you have.";
        return;
    }

    QSqlQuery query = server->getSqlQuery();
    query.prepare("UPDATE users SET level=?,address=?,phone=?,country=?,language=?,id_tree=?,enabled=?,surname=?,name=?,birth_date=?,picture=? WHERE id=?;");
    query.addBindValue(request["level"]);
    query.addBindValue(request["address"]);
    query.addBindValue(request["phone"]);
    query.addBindValue(request["country"]);
    query.addBindValue(request["language"]);
    query.addBindValue(request["id_tree"]);
    query.addBindValue(request["enabled"]);
    query.addBindValue(request["surname"]);
    query.addBindValue(request["name"]);
    query.addBindValue(request["birth_date"]);
    query.addBindValue(request["picture"]);
    query.addBindValue(request["UserId"]);

    if ( ! query.exec())
    {
        response["Error"]   = 5;
        response["ErrorMesssage"]   = "UserId " + request["UserId"].toString() + " not found.";
        return;
    }

    response["Success"] = true;
}

void UserManagment::createNewUser(quint32 userId, const QVariantHash& request,QVariantHash& response)
{
    if ( ! request.contains("login") || ! request.contains("password")
      || ! request.contains("level") ||  ! request.contains("address") ||  ! request.contains("phone")
      || ! request.contains("country") || ! request.contains("language") ||  ! request.contains("id_tree")
      || ! request.contains("surname") || ! request.contains("name") || ! request.contains("birth_date")
      || ! request.contains("picture") || ! request.contains("enabled"))
    {
        response["Error"]   = 2;
        response["ErrorMesssage"]   = "Invalid request: You must fill 'login','password','level','address','phone','counrty','language','id_tree','enabled','surname','name','birth_date','picture'";
        return;
    }

    if (request["level"].toInt() < server->getLevel(userId))
    {
        response["Error"]   = 3;
        response["ErrorMesssage"]   = "Permition denied: You can't give more privileges than you have.";
        return;
    }

    QSqlQuery query = server->getSqlQuery();
    query.prepare("INSERT INTO users (login,password,level,address,phone,country,language,id_tree,enabled,surname,name,birth_date,picture) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?);");
    query.addBindValue(request["login"]);
    query.addBindValue(request["password"]);
    query.addBindValue(request["level"]);
    query.addBindValue(request["address"]);
    query.addBindValue(request["phone"]);
    query.addBindValue(request["country"]);
    query.addBindValue(request["language"]);
    query.addBindValue(request["id_tree"]);
    query.addBindValue(request["enabled"]);
    query.addBindValue(request["surname"]);
    query.addBindValue(request["name"]);
    query.addBindValue(request["birth_date"]);
    query.addBindValue(request["picture"]);

    query.exec();

    response["UserId"] = query.lastInsertId();
    response["Success"] = true;
}

void UserManagment::disableUser(quint32 userId, const QVariantHash& request, QVariantHash& response)
{
    if (server->getLevel(userId) > LEVEL_ADMINISTRATOR)
    {
        response["Error"]   = 3;
        response["ErrorMesssage"]   = "Permition denied.";
        return;
    }

    QSqlQuery query = server->getSqlQuery();
    query.prepare("UPDATE id,enabled users SET (enabled=(enabled+1)%2) WHERE id=?;");
    query.addBindValue(request["userId"]);
    query.exec();
    response["id"]    = query.value(0);
    response["enabled"]    = query.value(1);
}
