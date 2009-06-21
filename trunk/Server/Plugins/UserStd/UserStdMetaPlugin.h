#ifndef USERSTDMETAPLUGIN_H
#define USERSTDMETAPLUGIN_H

#include "../../../Common/MetaPlugin.h"
#include "../../../Common/DataImplementations/UserDataStd/UserDataStdPlugin.h"

class UserStdMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline UserStdMetaPlugin() {
      pluginList.append(new UserDataStdPlugin);
  }
};

Q_EXPORT_PLUGIN2(UserStdMetaPlugin, UserStdMetaPlugin);

#endif // USERSTDMETAPLUGIN_H
