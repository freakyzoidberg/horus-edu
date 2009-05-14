#ifndef MODULEPACKET_H
#define MODULEPACKET_H

#include <QVariant>

//! communication class between server plugin and a client plugin
class PluginPacket
{
public:
    inline PluginPacket() {}
    inline PluginPacket(const QByteArray& target, const QVariant& _data) { targetPlugin = target; data = _data; }

    //! version of the source plugin. For a plugin, it's not neccessary to fill this value
    quint8     packetVersion;
    //! source plugin. For a plugin, it's not neccessary to fill this value
    QByteArray sourcePlugin;

    //! target plugin
    QByteArray targetPlugin;
    //! data of the packet
    QVariant   data;
};

#endif // MODULEPACKET_H
