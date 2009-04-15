#include "CommModule.h"


CommModule::CommModule(const char* src, const char* srcVer, const char* dest, const QByteArray& data) : CommPacket(CommPacket::MODULE)
{
    moduleSource = src;
    moduleSourceVersion = srcVer;
    moduleDestination = dest;
    moduleData = data;
}

CommModule::CommModule(QByteArray& a) : CommPacket(CommPacket::MODULE)
{
    moduleSource = a.mid(1, a[0]);
    a.remove(0,a[0] + 1);

    moduleSourceVersion = a.mid(1, a[0]);
    a.remove(0,a[0] + 1);

    moduleDestination = a.mid(1, a[0]);
    a.remove(0,a[0] + 1);

    moduleData = a;
}

const QByteArray CommModule::getPacket()
{
    QByteArray a = CommPacket::getPacket();

    a.append(moduleSource.length());
    a.append(moduleSource);

    a.append(moduleSourceVersion.length());
    a.append(moduleSourceVersion);

    a.append(moduleDestination.length());
    a.append(moduleDestination);

    a.append(moduleData);

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
             <<  "source:"    << cm.moduleSource
             << " sourceVer:" << cm.moduleSourceVersion
             << " dest:"      << cm.moduleDestination
             << " size: "     << cm.moduleData.length();
}
