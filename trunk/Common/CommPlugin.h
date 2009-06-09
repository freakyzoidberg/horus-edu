#ifndef COMMMODULE_H
#define COMMMODULE_H

#include "CommPacket.h"
#include "PluginPacket.h"

/*!
 * If the "messageType" of the "CommunicationContainer" is "MODULE_COMM"
 * there is this class inside "content".
 * it's for the comunication between a plugin client and a plugin server
 */
class CommPlugin : public CommPacket
{
public:
    CommPlugin(const QByteArray&);
    CommPlugin(const PluginPacket&);
    const QByteArray    getPacket() const;

    //! content of the packet (visible by the plugin)
    PluginPacket        packet;

private:
    void                read(const QByteArray&);
    void                write(QByteArray&) const;
};

QDebug operator<<(QDebug, const CommPlugin&);

#endif // COMMMODULE_H
