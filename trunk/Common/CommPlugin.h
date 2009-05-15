#ifndef COMMPLUGIN_H
#define COMMPLUGIN_H

#include "CommPacket.h"
#include "PluginPacket.h"

/*!
 * If the "messageType" of the "CommunicationContainer" is "PLUGIN"
 * the content is in the PluginPacket
 */
//! Communication packet for the comunication between a plugin client and a plugin server
class CommPlugin : public CommPacket
{
public:
    CommPlugin(QByteArray&);
    CommPlugin(const PluginPacket&);
    const QByteArray    getPacket();

    //! content of the packet (visible by the plugin)
    PluginPacket packet;

private:
    void                read(QByteArray&);
    void                write(QByteArray&);
};

QDebug operator<<(QDebug, const CommPlugin&);

#endif // COMMPLUGIN_H
