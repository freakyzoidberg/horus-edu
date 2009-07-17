#ifndef MAINFRAMEMETAPLUGIN_H
#define MAINFRAMEMETAPLUGIN_H

#include "../../../Common/MetaPlugin.h"

#include "Src/MainFrame.h"

class MainFrameMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline MainFrameMetaPlugin() {
      Plugin* p = new MainFrame();
      pluginList.append(p);
      //PluginManager().addPlugin(p);
  }
};

/* maybe put this lines in a cpp if this file is include by an other file */
// declare instance of the plugin
Q_EXPORT_PLUGIN2(MainFrameMetaPlugin, MainFrameMetaPlugin);

//Q_DECL_IMPORT QHash<QString,Plugin*> PluginManager::_plugins;
//Q_DECL_IMPORT const QHash<QString, Plugin*>& PluginManager::plugins() const;

#endif // MAINFRAMEMETAPLUGIN_H
