#include "CommModule.h"

CommModule::CommModule()
{
}

CommModule::CommModule(const char* src, const char* srcVer, const char* dest)
{
    moduleSource = src;
    moduleSourceVersion = srcVer;
    moduleDestination = dest;
}

QDataStream& operator<<(QDataStream& ds, CommModule& cm)
{
    ds << cm.moduleSource;
    ds << cm.moduleSourceVersion;
    ds << cm.moduleDestination;
    qDebug() << "->[out Module]" << cm;
    return ds;
}

QDataStream& operator>>(QDataStream& ds, CommModule& cm)
{
    ds >> cm.moduleSource;
    ds >> cm.moduleSourceVersion;
    ds >> cm.moduleDestination;
    qDebug() << "->[ in Module]" << cm;
    return ds;
}

QDebug operator<<(QDebug d, CommModule& cm)
{
    return d <<  "moduleSource ="        << cm.moduleSource
             << " moduleSourceVersion =" << cm.moduleSourceVersion
             << " moduleDestination ="   << cm.moduleDestination;
}
