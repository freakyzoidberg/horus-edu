#ifndef MODULEPACKET_H
#define MODULEPACKET_H

#include <QVariant>

class ModulePacket
{
public:
    inline ModulePacket() {}
    inline ModulePacket(const QByteArray& target, const QVariant& _data) { targetModule = target; data = _data; }

    quint8     packetVersion;
    QByteArray sourceModule;

    QByteArray targetModule;
    QVariant   data;
};

#endif // MODULEPACKET_H
