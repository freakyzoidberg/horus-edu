#include "UserManagement.h"
#include <QDebug>
#include <QHash>

Q_EXPORT_PLUGIN2(UserManagement, UserManagement)

UserManagement::UserManagement()
{
    requestFunctions["changePassword"] = &UserManagement::changePassword;
    requestFunctions["listUsers"]    = &UserManagement::listUsers;
    requestFunctions["getUserInfo"]    = &UserManagement::getUserInfo;
    requestFunctions["setUserInfo"]    = &UserManagement::setUserInfo;
    requestFunctions["createNewUser"]  = &UserManagement::createNewUser;
    requestFunctions["disableUser"]    = &UserManagement::disableUser;
}

void UserManagement::recvPacket(quint32 userId, const PluginPacket& request)
{
    PluginPacket response(request.sourcePlugin, request.request);

    QVariantHash reqHash = request.data.toHash();

    if ( ! reqHash.contains("UserId"))
        reqHash["UserId"] = userId;

    if (reqHash["UserId"].toUInt() != userId && server->getLevel(userId) > LEVEL_ADMINISTRATOR)
    {
        response.error = 3;
        response.errorMessage = "Permition denied.";
    }

    if ( ! response.error)
        (this->*requestFunctions.value(request.request,//go to the target method
                                       &UserManagement::unknownRequest)) //or if it'sunknown request
                                                                       (userId, reqHash, response);//parameters

    //send response
    server->sendPacket(userId, response);
}

void UserManagement::unknownRequest(quint32, const QVariantHash&, PluginPacket& response)
{
    response.error          = 1;
    response.errorMessage   = "Unknow request.";
}

void UserManagement::changePassword(quint32 userId, const QVariantHash& request, PluginPacket& response)
{
    if ( ! request.contains("password"))
    {
        response.error        = 2;
        response.errorMessage = "Invalid request: You must fill 'password'";
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
        response.error        = 2;
        response.errorMessage = "Invalid request: You must fill 'OldPassword'";
        return;
    }

    query.addBindValue(request["UserId"]);
    if ( ! query.exec() || ! query.numRowsAffected() == 1)
    {
        response.error        = 4;
        response.errorMessage = "Passwords doesn't match.";
        return;
    }
}

void UserManagement::listUsers(quint32 userId, const QVariantHash& request,PluginPacket& response)
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
        response.error        = 6;
        response.errorMessage = "Database error.";
        return;
    }

    QVariantList list;
    while (query.next())
    {
        QVariantHash user;
        user["id"]         = query.value(0);
        user["login"]      = query.value(1);
        user["id_tree"]    = query.value(12);

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
            user["enabled"]    = query.value(13);
        }
        list.append(user);
    }
    response.data = list;
}

void UserManagement::getUserInfo(quint32, const QVariantHash& request,PluginPacket& response)
{
    QSqlQuery query = server->getSqlQuery();
    query.prepare("SELECT login,level,last_login,surname,name,birth_date,picture,address,phone,country,language,id_tree,enabled FROM users WHERE id=?;");
    query.addBindValue(request.value("UserId"));
    if ( ! query.exec() || ! query.next())
    {
        response.error        = 5;
        response.errorMessage = "UserId " + request["UserId"].toString() + " not found.";
        return;
    }

    QVariantHash resp;
    resp["login"]      = query.value(0);
    resp["level"]      = query.value(1);
    resp["last_login"] = query.value(2);
    resp["surname"]    = query.value(3);
    resp["name"]       = query.value(4);
    resp["birth_date"] = query.value(5);
    resp["picture"]    = query.value(6);
    resp["address"]    = query.value(7);
    resp["phone"]      = query.value(8);
    resp["country"]    = query.value(9);
    resp["language"]   = query.value(10);
    resp["id_tree"]    = query.value(11);
    resp["enabled"]    = query.value(12);
    response.data = resp;
}

void UserManagement::setUserInfo(quint32 userId, const QVariantHash& request,PluginPacket& response)
{
    if ( ! request.contains("level") ||  ! request.contains("address") ||  ! request.contains("phone")
      || ! request.contains("country") || ! request.contains("language") || ! request.contains("id_tree")
      || ! request.contains("surname") || ! request.contains("name") || ! request.contains("birth_date")
      || ! request.contains("picture") || ! request.contains("enabled"))
    {
        response.error        = 2;
        response.errorMessage = "Invalid request: You must fill 'level','address','phone','counrty','language','id_tree','enabled','surname','name','birth_date','picture'";
        return;
    }

    if (request["level"].toInt() < server->getLevel(userId))
    {
        response.error        = 3;
        response.errorMessage = "Permition denied: You can't give more privileges than you have.";
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
        response.error        = 5;
        response.errorMessage = "UserId " + request["UserId"].toString() + " not found.";
        return;
    }
}

void UserManagement::createNewUser(quint32 userId, const QVariantHash& request,PluginPacket& response)
{
    if ( ! request.contains("login") || ! request.contains("password")
      || ! request.contains("level") ||  ! request.contains("address") ||  ! request.contains("phone")
      || ! request.contains("country") || ! request.contains("language") ||  ! request.contains("id_tree")
      || ! request.contains("surname") || ! request.contains("name") || ! request.contains("birth_date")
      || ! request.contains("picture") || ! request.contains("enabled"))
    {
        response.error        = 2;
        response.errorMessage = "Invalid request: You must fill 'login','password','level','address','phone','counrty','language','id_tree','enabled','surname','name','birth_date','picture'";
        return;
    }

    if (request["level"].toInt() < server->getLevel(userId))
    {
        response.error        = 3;
        response.errorMessage = "Permition denied: You can't give more privileges than you have.";
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

    QVariantHash resp = request;
    resp["UserId"] = query.lastInsertId();
    response.data = resp;
}

void UserManagement::disableUser(quint32 userId, const QVariantHash& request, PluginPacket& response)
{
    if (server->getLevel(userId) > LEVEL_ADMINISTRATOR)
    {
        response.error        = 3;
        response.errorMessage = "Permition denied. Only ADMINISTRATOR and ROOT can disable a user.";
        return;
    }

    QSqlQuery query = server->getSqlQuery();
    query.prepare("UPDATE id,enabled users SET (enabled=(enabled+1)%2) WHERE id=?;");
    query.addBindValue(request["userId"]);
    query.exec();

    QVariantHash resp;
    resp["id"]    = query.value(0);
    resp["enabled"]    = query.value(1);
}
