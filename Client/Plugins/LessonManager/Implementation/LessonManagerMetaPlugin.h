#ifndef LESSONMANAGERMETAPLUGIN_H
#define LESSONMANAGERMETAPLUGIN_H

#include "../../../../Common/MetaPlugin.h"

#include "LessonManager.h"

class LessonManagerMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline LessonManagerMetaPlugin() {
      Plugin* p = new LessonManager();
      pluginList.append(p);
  }
};

/* maybe put this lines in a cpp if this file is include by an other file */
// declare instance of the plugin
Q_EXPORT_PLUGIN2(LessonManagerMetaPlugin, LessonManagerMetaPlugin);

#endif // LESSONMANAGERMETAPLUGIN_H
