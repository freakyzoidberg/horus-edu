#ifndef TESTNETWORKPLUGIN_H
#define TESTNETWORKPLUGIN_H

#include "../../NetworkPlugin.h"

class UserData;
class TestNetworkPlugin : public NetworkPlugin
{
    Q_OBJECT
    Q_INTERFACES(NetworkPluginServer Plugin)

    // Plugin Interface
public:
    inline const QString   pluginName()    const { return "TestNetworkPlugin"; }
    inline const QString   pluginVersion() const { return "0.1"; }

    // NetworkPlugin Interface
public slots:
    void receivePacket(UserData* user, const PluginPacket);
};

#endif // TESTNETWORKPLUGIN_H
