#ifndef FILEBASECLIENTMETAPLUGIN_H
#define FILEBASECLIENTMETAPLUGIN_H

#include "../../../Common/MetaPlugin.h"

#include "../../../Common/DataImplementations/FileDataBase/FileDataBasePlugin.h"
#include "FileNetworkPlugin.h"

class FileBaseClientMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline FileBaseClientMetaPlugin() {
      FileDataBasePlugin* dataPlugin = new FileDataBasePlugin;
      pluginList.append(dataPlugin);
      pluginList.append(new FileNetworkPlugin(dataPlugin));
  }
};

Q_EXPORT_PLUGIN2(FileBaseClientMetaPlugin, FileBaseClientMetaPlugin);

#endif // FILEBASECLIENTMETAPLUGIN_H
