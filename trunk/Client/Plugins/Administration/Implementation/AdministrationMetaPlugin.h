#ifndef ADMINISTRATIONMETAPLUGIN_H
#define ADMINISTRATIONMETAPLUGIN_H

#include "../../../Common/MetaPlugin.h"

#include "Administration.h"

class AdministrationMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline AdministrationMetaPlugin() {
      Plugin* p = new Administration();
      pluginList.append(p);
      //PluginManager().addPlugin(p);
  }
};

/* maybe put this lines in a cpp if this file is include by an other file */
// declare instance of the plugin
Q_EXPORT_PLUGIN2(AdministrationMetaPlugin, AdministrationMetaPlugin);


#endif // ADMINISTRATIONMETAPLUGIN_H
