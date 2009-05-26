#include "TreeManagement.h"

Q_EXPORT_PLUGIN2(TreeManagement, TreeManagement);

TreeManagement::TreeManagement()
{
    qDebug() << "TreeManagement has arrived";
}

TreeManagement::~TreeManagement()
{
    qDebug() << "bye bye TreeManagement";
}

void TreeManagement::recvPacket(quint32 userId, const PluginPacket& packet)
{
    server->sendPacket(userId, PluginPacket(packet.sourcePlugin, packet.data));
    QByteArray* toto = server->GetSql();
    delete toto;
    toto = server->GetSql();
    delete toto;
    toto = server->GetSql();
    delete toto;
    toto = server->GetSql();
    delete toto;
    toto = server->GetSql();
    delete toto;
    toto = server->GetSql();
    delete toto;
    toto = server->GetSql();
    delete toto;
    toto = server->GetSql();
    delete toto;
    toto = server->GetSql();
    delete toto;
    toto = server->GetSql();
    delete toto;
    toto = server->GetSql();
    delete toto;
}
