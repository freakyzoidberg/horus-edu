#ifndef PLUGINPACKET_H
#define PLUGINPACKET_H

#include <QDebug>
#include <QVariant>
#include <QDataStream>

//! communication class between server plugin and a client plugin
class PluginPacket
{
public:
    inline PluginPacket() { error=0; }
    inline PluginPacket(const QByteArray& _target, const QByteArray& _request, const QVariant& _data=QVariant()) { targetPlugin=_target; request=_request; data=_data; error=0;}

    //! version of the source plugin. For a plugin, it's not neccessary to fill this value
    QByteArray packetVersion;
    //! source plugin. For a plugin, it's not neccessary to fill this value
    QByteArray sourcePlugin;

    //! target plugin
    QByteArray targetPlugin;
    //! request
    QByteArray request;
    //! error code
    quint16    error;
    //! error message
    QString    errorMessage;
    //! data of the packet
    QVariant   data;
};

QDebug& operator<<(QDebug& d, const PluginPacket& p);
QDataStream& operator<<(QDataStream& d, const PluginPacket& p);
QDataStream& operator>>(QDataStream& d, PluginPacket& p);

#endif // PLUGINPACKET_H
