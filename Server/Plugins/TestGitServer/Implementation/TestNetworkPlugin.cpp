#include "TestNetworkPlugin.h"

void TestNetworkPlugin::receivePacket(UserData* user, const PluginPacket)
{
    emit sendPacket(user, PluginPacket("TestNetworkPlugin", "test retour", "test retour"));
}
