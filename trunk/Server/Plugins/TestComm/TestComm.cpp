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

const QByteArray TestComm::getName() const
{
    return "TestComm";
}

const QByteArray TestComm::getVersion() const
{
    return "42";
}

void TestComm::recvPacket(quint32 userId, const ModulePacket& packet) const
{
    ModulePacket resp;
    resp.packetVerion = packet.packetVerion;
    resp.sourceModule = packet.targetModule;
    resp.targetModule = packet.sourceModule;
    resp.dataList = packet.dataList;

    emit sendPacket(userId, resp);
}
