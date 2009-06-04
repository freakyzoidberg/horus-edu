#include "AdministrationPlugin.h"
#include <QDebug>
#include "../../ClientEvents.h"

Q_EXPORT_PLUGIN2(Administration, Administration)

extern QEvent::Type ClientEvents::PluginEvent;

Administration::Administration()
{
    this->adminF = new AdminFram(this->network);
}

QWidget             *Administration::getWidget()
{
    this->adminF = new AdminFram(this->network);
    return (this->adminF);
}

void Administration::recvPacket(const PluginPacket& packet)
{
        this->adminF->packetManager(packet.data.toHash());
}

bool    Administration::event(QEvent *event)
{
    if(event->type() == ClientEvents::PluginEvent)
    {
        qDebug() << "here";
        PluginEvent *pe = static_cast<PluginEvent *>(event);
        this->adminF->packetManager(pe->pack.data.toHash());
    }
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
