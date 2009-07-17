#ifndef USERBASESERVERMETAPLUGIN_H
#define USERBASESERVERMETAPLUGIN_H

#include "../../../Common/MetaPlugin.h"

#include "../../../Common/DataImplementations/UserDataBase/UserDataBasePlugin.h"

class UserBaseServerMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline UserBaseServerMetaPlugin() {
      pluginList.append(new UserDataBasePlugin);
  }
};

/* maybe put this lines in a cpp if this file is include by an other file */
// declare instance of the plugin
Q_EXPORT_PLUGIN2(UserBaseServerMetaPlugin, UserBaseServerMetaPlugin);

//Q_IMPORT_PLUGIN(PluginManager);
//Q_DECL_IMPORT QHash<QString,Plugin*>* PluginManager::_plugins;

#endif // USERBASESERVERMETAPLUGIN_H
