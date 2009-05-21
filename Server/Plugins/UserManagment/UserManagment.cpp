#include "UserManagment.h"

#include <QDebug>

Q_EXPORT_PLUGIN2(UserManagment, UserManagment)

void UserManagment::recvPacket(quint32 userId, const PluginPacket& packet) const
{
    QHash<QString,QVariant> response;

//    if (packet.data.type() == response.t)

    server->sendPacket(userId, PluginPacket(packet.sourcePlugin, packet.data));
}
