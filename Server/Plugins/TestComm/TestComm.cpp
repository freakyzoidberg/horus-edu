#include "TestComm.h"

#include <QDebug>

Q_EXPORT_PLUGIN2(TestComm, TestComm)

TestComm::TestComm()
{
    qDebug() << "He Ho !! je suis la!!!";
}

TestComm::~TestComm()
{
    qDebug() << "gniiiiiiiiIIIIIII";
}

void TestComm::recvPacket(quint32 userId, const PluginPacket& packet) const
{
    server->sendPacket(userId, PluginPacket(packet.sourcePlugin, packet.data));
}
