#include "AdministrationPlugin.h"

Q_EXPORT_PLUGIN2(Administration, Administration)

Administration::Administration()
{
    this->adminF = new AdminFram(this->network);
}

QWidget             *Administration::getWidget()
{
    return this->adminF;
}

void Administration::recvPacket(const PluginPacket& packet)
{
    this->adminF->packetManager(packet.data.toHash());
}

bool    Administration::event(QEvent *event)
{
    return (QObject::event(event));
}

const QByteArray   Administration::getName() const
{
    return ("Administration");
}

const QByteArray   Administration::getVersion() const
{
    return ("1.0");
}

QStringList   Administration::getPluginsConflicts() const
{
    return (QStringList());
}

QStringList   Administration::getPluginsRequired() const
{
    return (QStringList());
}

QStringList   Administration::getPluginsRecommended() const
{
    return (QStringList());
}

QStringList   Administration::getExports() const
{
    return (QStringList());
}
