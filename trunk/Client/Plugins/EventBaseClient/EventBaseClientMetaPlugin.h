#ifndef EVENTBASECLIENTMETAPLUGIN_H
#define EVENTBASECLIENTMETAPLUGIN_H

#include "../../../Common/MetaPlugin.h"

#include "../../../Common/DataImplementations/EventDataBase/EventDataBasePlugin.h"

class EventBaseServerMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
	inline EventBaseServerMetaPlugin() {
	  pluginList.append(new EventDataBasePlugin);
  }
};

/* maybe put this lines in a cpp if this file is include by an other file */
// declare instance of the plugin
Q_EXPORT_PLUGIN2(EventBaseServerMetaPlugin, EventBaseServerMetaPlugin);

#endif // EVENTBASECLIENTMETAPLUGIN_H
