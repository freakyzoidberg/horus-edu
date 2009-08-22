#ifndef ATTENDANCEMETAPLUGIN_H
#define ATTENDANCEMETAPLUGIN_H

#include "../../../../Common/MetaPlugin.h"

#include "Attendance.h"

class AttendanceMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline AttendanceMetaPlugin() {
      Plugin* p = new Attendance();
      pluginList.append(p);
  }
};

/* maybe put this lines in a cpp if this file is include by an other file */
// declare instance of the plugin
Q_EXPORT_PLUGIN2(AttendanceMetaPlugin, AttendanceMetaPlugin);

#endif // ATTENDANCEMETAPLUGIN_H
