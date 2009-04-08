#include "CommModule.h"

CommModule::CommModule() : CommPacket(CommPacket::MODULE)
{
}

CommModule::CommModule(const char* src, const char* srcVer, const char* dest, const QByteArray& data) : CommPacket(CommPacket::MODULE)
{
    moduleSource = src;
    moduleSourceVersion = srcVer;
    moduleDestination = dest;
    moduleData = data;
}

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

QDebug operator<<(QDebug d, CommModule& cm)
{
    return d << (CommPacket&)cm
             <<  "source:"    << cm.moduleSource
             << " sourceVer:" << cm.moduleSourceVersion
             << " dest:"      << cm.moduleDestination
             << " size: "     << cm.moduleData.length();
}
