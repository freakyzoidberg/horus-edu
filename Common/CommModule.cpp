#include "CommModule.h"

CommModule::CommModule() : CommPacket(CommPacket::MODULE)
{
}

CommModule::CommModule(const char* src, const char* srcVer, const char* dest) : CommPacket(CommPacket::MODULE)
{
    moduleSource = src;
    moduleSourceVersion = srcVer;
    moduleDestination = dest;
}

QDataStream& operator<<(QDataStream& ds, CommModule& cm)
{
    qDebug() << "[out]" << cm;
    return ds << (CommPacket&)cm << cm.moduleSource << cm.moduleSourceVersion << cm.moduleDestination;
}

QDataStream& operator>>(QDataStream& ds, CommModule& cm)
{
    ds >> cm.moduleSource >> cm.moduleSourceVersion >> cm.moduleDestination;
    qDebug() << "[ in]" << cm;
    return ds;
}

QDebug operator<<(QDebug d, CommModule& cm)
{
    return d << (CommPacket&)cm
             <<  "source:"    << cm.moduleSource
             << " sourceVer:" << cm.moduleSourceVersion
             << " dest:"      << cm.moduleDestination;
}
