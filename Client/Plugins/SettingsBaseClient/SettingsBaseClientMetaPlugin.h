#ifndef USERBASESERVERMETAPLUGIN_H
#define USERBASESERVERMETAPLUGIN_H

#include "../../../Common/MetaPlugin.h"

#include "../../../Common/DataImplementations/SettingsDataBase/SettingsDataBasePlugin.h"

class SettingsBaseClientMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline SettingsBaseClientMetaPlugin() {
      pluginList.append(new SettingsDataBasePlugin);
  }
};

Q_EXPORT_PLUGIN2(SettingsBaseClientMetaPlugin, SettingsBaseClientMetaPlugin);

#endif // USERBASESERVERMETAPLUGIN_H
