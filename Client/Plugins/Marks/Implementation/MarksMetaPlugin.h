#ifndef MARKSMETAPLUGIN_H
#define MARKSMETAPLUGIN_H

#include "../../../../Common/MetaPlugin.h"

#include "Marks.h"

class MarksMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline MarksMetaPlugin() {
      Plugin* p = new Marks();
      pluginList.append(p);
  }
};

/* maybe put this lines in a cpp if this file is include by an other file */
// declare instance of the plugin
Q_EXPORT_PLUGIN2(MarksMetaPlugin, MarksMetaPlugin);

#endif // MARKSMETAPLUGIN_H
