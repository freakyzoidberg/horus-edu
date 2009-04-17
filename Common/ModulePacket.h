#ifndef MODULEPACKET_H
#define MODULEPACKET_H

class ModulePacket
{
public:
    inline ModulePacket(const QByteArray& version="", const QByteArray& source="", const QByteArray& target="", const QByteArray& _data="")
                        { packetVersion = version;       sourceModule = source;       targetModule = target;               data = _data; }

    QByteArray packetVersion;
    QByteArray sourceModule;
    QByteArray targetModule;
    QByteArray data;
};

#endif // MODULEPACKET_H
