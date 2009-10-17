#ifndef CALENDARMETAPLUGIN_H
#define CALENDARMETAPLUGIN_H

#include "../../../Common/MetaPlugin.h"

#include "Implementation/calendar.h"

class CalendarMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline CalendarMetaPlugin() {
      pluginList.append(new Calendar());
  }
};

/* maybe put this lines in a cpp if this file is include by an other file */
// declare instance of the plugin
Q_EXPORT_PLUGIN2(CalendarMetaPlugin, CalendarMetaPlugin);

#endif // CALENDARMETAPLUGIN_H
