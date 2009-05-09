#include <QByteArray>

#include "CommModule.h"

CommModule::CommModule(const ModulePacket& mp)
    : CommPacket(CommPacket::MODULE)
{
    packet = mp;
}

CommModule::CommModule(QByteArray& a)
    : CommPacket(CommPacket::MODULE)
{
    read(a);
}

const QByteArray CommModule::getPacket()
{
    QByteArray a;
    CommPacket::write(a);
    write(a);
    return a;
}

void CommModule::read(QByteArray& a)
{
    QDataStream stream(&a, QIODevice::ReadOnly);
    stream >> packet.packetVersion
           >> packet.sourceModule
           >> packet.targetModule
           >> packet.data;
}

void CommModule::write(QByteArray& a)
{
    QDataStream stream(&a, QIODevice::WriteOnly);
    stream.device()->seek(a.length());

    stream << packet.packetVersion
           << packet.sourceModule
           << packet.targetModule
           << packet.data;
}

QDebug operator<<(QDebug d, CommModule& cm)
{
    return d << (CommPacket&)cm
             << cm.packet.packetVersion
             << cm.packet.sourceModule
             << cm.packet.targetModule
             << cm.packet.data;
}
