#ifndef NEWSMETAPLUGIN_H
#define NEWSSMETAPLUGIN_H

#include "../../../../Common/MetaPlugin.h"

#include "News.h"

class NewsMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline NewsMetaPlugin() {
      Plugin* p = new News();
      pluginList.append(p);
  }
};

/* maybe put this lines in a cpp if this file is include by an other file */
// declare instance of the plugin
Q_EXPORT_PLUGIN2(NewsMetaPlugin, NewsMetaPlugin);

#endif // NEWSMETAPLUGIN_H
