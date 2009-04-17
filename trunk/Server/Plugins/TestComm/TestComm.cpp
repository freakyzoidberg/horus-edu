#include "TestComm.h"

Q_EXPORT_PLUGIN2(TestComm, TestComm)

TestComm::TestComm()
{
    qDebug() << "He Ho !! je suis la!!!";
}

TestComm::~TestComm()
{
    qDebug() << "gniiiiiiiiIIIIIII";
}

void TestComm::recvPacket(quint32 userId, const ModulePacket& packet) const
{
    server->sendPacket(userId, ModulePacket(version(), name(), packet.sourceModule, packet.data));
}
