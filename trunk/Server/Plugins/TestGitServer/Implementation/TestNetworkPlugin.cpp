#include "TestNetworkPlugin.h"

void TestNetworkPlugin::receivePacket(UserData* user, const PluginPacket packet)
{
    emit sendPacket(user, PluginPacket("TestNetworkPlugin", "test retour", "test retour"));
}
