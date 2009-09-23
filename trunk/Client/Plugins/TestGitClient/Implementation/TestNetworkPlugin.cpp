#include "TestNetworkPlugin.h"

void TestNetworkPlugin::sendTest()
{
    emit sendPacket(PluginPacket("TestNetworkPlugin", "test aller", "test aller"));
}

void TestNetworkPlugin::receivePacket(const PluginPacket)
{
}
