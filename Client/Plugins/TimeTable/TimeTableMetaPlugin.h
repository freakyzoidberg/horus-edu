#ifndef TIMETABLEMETAPLUGIN_H
#define TIMETABLEMETAPLUGIN_H

#include "../../../Common/MetaPlugin.h"

#include "Implementation/TimeTable.h"

class TimeTableMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline TimeTableMetaPlugin() {
      pluginList.append(new TimeTable());
  }
};

/* maybe put this lines in a cpp if this file is include by an other file */
// declare instance of the plugin
Q_EXPORT_PLUGIN2(TimeTableMetaPlugin, TimeTableMetaPlugin);


#endif // TIMETABLEMETAPLUGIN_H
