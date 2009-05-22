#include "TreeManagement.h"

Q_EXPORT_PLUGIN2(TreeManagement, TreeManagement)

TreeManagement::TreeManagement()
{
    qDebug() << "TreeManagement has arrived";
}

TreeManagement::~TreeManagement()
{
    qDebug() << "bye bye TreeManagement";
}

void TreeManagement::recvPacket(quint32 userId, const PluginPacket& packet) const
{
    server->sendPacket(userId, PluginPacket(packet.sourcePlugin, packet.data));
}
