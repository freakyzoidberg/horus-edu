#ifndef MODULEPACKET_H
#define MODULEPACKET_H

class ModulePacket
{
public:
    inline ModulePacket(quint8 version=0, const QByteArray& source="", const QByteArray& target="", const QByteArray& _data="")
             { packetVersion = version;       sourceModule = source;       targetModule = target;               data = _data; }

    quint8     packetVersion;
    QByteArray sourceModule;
    QByteArray targetModule;
    QByteArray data;
};

#endif // MODULEPACKET_H
