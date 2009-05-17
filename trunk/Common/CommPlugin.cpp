#include <QByteArray>

#include "CommPlugin.h"

CommPlugin::CommPlugin(const PluginPacket& mp)
    : CommPacket(CommPacket::PLUGIN)
{
    packet = mp;
}

CommPlugin::CommPlugin(QByteArray& a)
    : CommPacket(CommPacket::PLUGIN)
{
    read(a);
}

const QByteArray CommPlugin::getPacket()
{
    QByteArray a;
    CommPacket::write(a);
    write(a);
    return a;
}

void CommPlugin::read(QByteArray& a)
{
    QDataStream stream(&a, QIODevice::ReadOnly);
    stream >> packet.packetVersion
           >> packet.sourcePlugin
           >> packet.targetPlugin
           >> packet.data;
}

void CommPlugin::write(QByteArray& a)
{
    QDataStream stream(&a, QIODevice::WriteOnly);
    stream.device()->seek(a.length());

    stream << packet.packetVersion
           << packet.sourcePlugin
           << packet.targetPlugin
           << packet.data;
}

QDebug operator<<(QDebug d, CommPlugin& cm)
{
    return d << (CommPacket&)cm
             << cm.packet.packetVersion
             << cm.packet.sourcePlugin
             << cm.packet.targetPlugin
             << cm.packet.data;
}
