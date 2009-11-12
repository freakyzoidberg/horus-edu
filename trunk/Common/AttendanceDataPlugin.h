#ifndef ATTENDANCEDATAPLUGIN_H
#define ATTENDANCEDATAPLUGIN_H

#include <QDateTime>
#include "DataPlugin.h"

class TreeData;
class AttendanceData;
class AttendanceDataPlugin : public DataPlugin
{
    Q_OBJECT
#ifdef HORUS_SERVER
    Q_INTERFACES(ServerDataPlugin)
#endif
#ifdef HORUS_CLIENT
    Q_INTERFACES(ClientDataPlugin)
#endif

public:
        virtual AttendanceData*	  newAttendance(TreeData* parent, QString name, UserData* user = 0) = 0;
};

#ifdef HORUS_SERVER
typedef AttendanceDataPlugin ServerAttendanceDataPlugin;
Q_DECLARE_INTERFACE(ServerAttendanceDataPlugin, "net.horus.ServerAttendanceDataPlugin/1.0");
#endif
#ifdef HORUS_CLIENT
typedef AttendanceDataPlugin ClientAttendanceDataPlugin;
Q_DECLARE_INTERFACE(ClientAttendanceDataPlugin, "net.horus.ClientAttendanceDataPlugin/1.0");
#endif

#endif // ATTENDANCEPLUGIN_H
