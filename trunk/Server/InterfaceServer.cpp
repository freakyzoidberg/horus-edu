#include "InterfaceServer.h"

void InterfaceServer::sendPacket(const quint32 userId, const ModulePacket& packet) const
{
    CommModule p = packet;
    User* usr = User::getUser(userId);
    if (usr)
    {
        qDebug() << "[out]" << p;
        usr->sendPacket( p.getPacket() );
    }
}

IServerPlugin* InterfaceServer::getModule(const char* name) const
{
    return 0;
}
