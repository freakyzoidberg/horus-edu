#ifndef PLUGINPACKET_H
#define PLUGINPACKET_H

#include <QDebug>
#include <QVariant>
#include <QDataStream>

class UserData;
//! communication class between server plugin and a client plugin
class PluginPacket
{
public:
    inline PluginPacket() { error=0; }
    inline PluginPacket(const QString& _target, const QString& _request, const QVariant& _data=QVariant()) { targetPlugin=_target; request=_request; data=_data; error=0;}

    //! version of the source plugin. For a plugin, it's not neccessary to fill this value
    QString packetVersion;
    //! source plugin. For a plugin, it's not neccessary to fill this value
    QString sourcePlugin;

    //! target plugin
    QString targetPlugin;
    //! request
    QString request;
    //! error code
    quint16    error;
    //! error message
    QString    errorMessage;
    //! data of the packet
    QVariant   data;

#ifdef HORUS_SERVER
    //! Just an information given by the server when receiving a packet. This field also need to be filled before sending a packet to this User.
    UserData* user;
#endif
};

QDebug& operator<<(QDebug& d, const PluginPacket& p);
QDataStream& operator<<(QDataStream& d, const PluginPacket& p);
QDataStream& operator>>(QDataStream& d, PluginPacket& p);

#endif // PLUGINPACKET_H
