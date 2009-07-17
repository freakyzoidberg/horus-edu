#ifndef USERSTDMETAPLUGIN_H
#define USERSTDMETAPLUGIN_H

#include "../../../Common/MetaPlugin.h"

#include "../../../Common/DataImplementations/UserDataBase/UserDataBasePlugin.h"

class UserBaseClientMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline UserBaseClientMetaPlugin() {
      pluginList.append(new UserDataBasePlugin);
  }
};

/* maybe put this lines in a cpp if this file is include by an other file */
// declare instance of the plugin
Q_EXPORT_PLUGIN2(UserBaseClientMetaPlugin, UserBaseClientMetaPlugin);

//Q_DECL_IMPORT QHash<QString,Plugin*> PluginManager::_plugins;

#endif // USERSTDMETAPLUGIN_H
