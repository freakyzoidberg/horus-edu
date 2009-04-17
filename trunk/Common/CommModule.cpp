#include "CommModule.h"

CommModule::CommModule(const ModulePacket& mp)
    : CommPacket(CommPacket::MODULE)
{
    packet = mp;
}

CommModule::CommModule(QByteArray& a)
    : CommPacket(CommPacket::MODULE)
{
    packet.packetVersion = a[0];

    packet.sourceModule = a.mid(2, a[1]);
    a.remove(0,a[1] + 2);

    packet.targetModule = a.mid(1, a[0]);
    a.remove(0,a[0] + 1);

    packet.data = a;
}

const QByteArray CommModule::getPacket()
{
    QByteArray a = CommPacket::getPacket();

    a.append(packet.packetVersion);

    a.append((char)packet.sourceModule.length());
    a.append(packet.sourceModule);

    a.append((char)packet.targetModule.length());
    a.append(packet.targetModule);

    a.append(packet.data);

    return a;
}

QDebug operator<<(QDebug d, CommModule& cm)
{
    return d << (CommPacket&)cm
             << cm.packet.packetVersion
             << cm.packet.sourceModule
             << cm.packet.targetModule
             << cm.packet.data;
}
