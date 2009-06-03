#include "AdministrationPlugin.h"

Q_EXPORT_PLUGIN2(Administration, Administration)

Administration::Administration()
{
    this->adminF = new AdminFram();
    modName.append("Administration");
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
    return modName;
}

const QByteArray   Administration::getVersion() const
{
    return modVersion;
}

QStringList   Administration::getPluginsConflicts() const
{
    return modConflicts;
}

QStringList   Administration::getPluginsRequired() const
{
    return modRequired;
}

QStringList   Administration::getPluginsRecommended() const
{
    return modRecommended;
}

QStringList   Administration::getExports() const
{
    return exports;
}
