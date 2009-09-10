#ifndef TESTNETWORKPLUGIN_H
#define TESTNETWORKPLUGIN_H

#include "../../../NetworkPlugin.h"

class TestNetworkPlugin : public NetworkPlugin
{
    Q_OBJECT
    Q_INTERFACES(NetworkPluginClient Plugin)

    // Plugin Interface
public:
    inline const QString   pluginName()    const { return "TestNetworkPlugin"; }
    inline const QString   pluginVersion() const { return "0.1"; }

    // NetworkPlugin Interface
public slots:
    void receivePacket(const PluginPacket);

    void sendTest();
};

#endif // TESTNETWORKPLUGIN_H
