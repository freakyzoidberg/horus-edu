#include "UserManagment.h"

#include <QDebug>
#include <QHash>

Q_EXPORT_PLUGIN2(UserManagment, UserManagment)

QHash<QByteArray,UserManagment::requestFunction> UserManagment::requestFunctions;

void UserManagment::recvPacket(quint32 userId, const PluginPacket& packet)
{
    if ( ! requestFunctions.count())
    {
        requestFunctions["changePassword"] = &UserManagment::changePassword;
        requestFunctions["createUser"]     = &UserManagment::createUser;
    }

    const QVariantHash request = packet.data.toHash();
    QVariantHash response;
    response["Request"] = request["Request"];
    response["Success"] = false;
//    response["Error"] = "Unknow error.";

    (this->*requestFunctions.value(request["Request"].toByteArray(),&UserManagment::unknownRequest))(request, response);
    server->sendPacket(userId, PluginPacket(packet.sourcePlugin, response));
}

//requestFunction::
