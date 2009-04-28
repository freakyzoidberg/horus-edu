#ifndef MODULEPACKET_H
#define MODULEPACKET_H

class ModulePacket
{
public:
    inline ModulePacket(const QByteArray& target="", const QByteArray& _data="") { targetModule = target; data = _data; }

    quint8     packetVersion;
    QByteArray sourceModule;

    QByteArray targetModule;
    QByteArray data;
};

#endif // MODULEPACKET_H
