#ifndef GRADEDATAPLUGIN_H
#define GRADEDATAPLUGIN_H

#include <QDateTime>
#include "DataPlugin.h"

class TreeData;
class GradeData;
class GradeDataPlugin : public DataPlugin
{
    Q_OBJECT
#ifdef HORUS_SERVER
    Q_INTERFACES(ServerDataPlugin)
#endif
#ifdef HORUS_CLIENT
    Q_INTERFACES(ClientDataPlugin)
#endif

public:

};

#ifdef HORUS_SERVER
typedef GradeDataPlugin ServerGradeDataPlugin;
Q_DECLARE_INTERFACE(ServerGradeDataPlugin, "net.horus.ServerGradeDataPlugin/1.0");
#endif
#ifdef HORUS_CLIENT
typedef GradeDataPlugin ClientGradeDataPlugin;
Q_DECLARE_INTERFACE(ClientGradeDataPlugin, "net.horus.ClientGradeDataPlugin/1.0");
#endif

#endif // GRADEDATAPLUGIN_H
