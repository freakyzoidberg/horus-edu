#include <QByteArray>

#include "CommPlugin.h"
#include "PluginPacket.h"

CommPlugin::CommPlugin(const PluginPacket& mp)
    : CommPacket(CommPacket::PLUGIN)
{
    packet = mp;
}

CommPlugin::CommPlugin(const QByteArray& a)
    : CommPacket(CommPacket::PLUGIN)
{
    read(a);
}

const QByteArray CommPlugin::getPacket() const
{
    QByteArray a;
    CommPacket::write(a);
    write(a);
    return a;
}

void CommPlugin::read(const QByteArray& a)
{
    QDataStream stream(a);
    stream.device()->seek(lenParent());
    stream >> packet;
}

void CommPlugin::write(QByteArray& a) const
{
    QDataStream stream(&a, QIODevice::WriteOnly);
    stream.device()->seek( lenParent() );
    stream << packet;
}

QDebug operator<<(QDebug d, const CommPlugin& cp)
{ return d
    << (CommPacket&)cp
    << cp.packet.sourcePlugin
    << cp.packet.targetPlugin
    << cp.packet.request
    //<< cm.packet // SEGFAULT ????
; }
