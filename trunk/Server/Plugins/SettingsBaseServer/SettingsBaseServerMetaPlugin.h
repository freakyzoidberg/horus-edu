#ifndef SETTINGSBASESERVERMETAPLUGIN_H
#define SETTINGSBASESERVERMETAPLUGIN_H

#include "../../../Common/MetaPlugin.h"

#include "../../../Common/DataImplementations/SettingsDataBase/SettingsDataBasePlugin.h"

class SettingsBaseServerMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline SettingsBaseServerMetaPlugin() {
      pluginList.append(new SettingsDataBasePlugin);
  }
};

Q_EXPORT_PLUGIN2(SettingsBaseServerMetaPlugin, SettingsBaseServerMetaPlugin);

#endif // SETTINGSBASESERVERMETAPLUGIN_H
