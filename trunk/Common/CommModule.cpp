#include "CommModule.h"

CommModule::CommModule(const ModulePacket& mp) : CommPacket(CommPacket::MODULE)
{
    packetVerion = mp.packetVerion;
    sourceModule = mp.sourceModule;
    targetModule = mp.targetModule;
    dataList = mp.dataList;
}

CommModule::CommModule(QByteArray& a) : CommPacket(CommPacket::MODULE)
{
    packetVerion = a.mid(1, a[0]);
    a.remove(0,a[0] + 1);

    sourceModule = a.mid(1, a[0]);
    a.remove(0,a[0] + 1);

    targetModule = a.mid(1, a[0]);
    a.remove(0,a[0] + 1);

    while ( ! a.isEmpty())
    {
        dataList.append(a.mid(1, a[0]));
        a.remove(0, a[0] + 1);
    }
}

const QByteArray CommModule::getPacket()
{
    QByteArray a = CommPacket::getPacket();

    a.append((char)packetVerion.length());
    a.append(packetVerion);

    a.append((char)sourceModule.length());
    a.append(sourceModule);

    a.append((char)targetModule.length());
    a.append(targetModule);

    foreach (const QByteArray line, dataList)
    {
        a.append((char)line.length());
        a.append(line);
    }

    return a;
}

/*
QDataStream& operator<<(QDataStream& ds, CommModule& cm)
{
    qDebug() << "[out]" << cm;
    return ds << (CommPacket&)cm << cm.moduleSource << cm.moduleSourceVersion << cm.moduleDestination << cm.moduleData;
}

QDataStream& operator>>(QDataStream& ds, CommModule& cm)
{
    ds >> cm.moduleSource >> cm.moduleSourceVersion >> cm.moduleDestination >> cm.moduleData;
    qDebug() << "[ in]" << cm;
    return ds;
}
*/
QDebug operator<<(QDebug d, CommModule& cm)
{
    return d << (CommPacket&)cm
             << cm.packetVerion
             << cm.sourceModule
             << cm.targetModule
             << cm.dataList;
}
