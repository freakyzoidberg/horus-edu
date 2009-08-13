#ifndef FILEBASECLIENTRMETAPLUGIN_H
#define FILEBASECLIENTMETAPLUGIN_H

#include "../../../Common/MetaPlugin.h"

#include "../../../Common/DataImplementations/FileDataBase/FileDataBasePlugin.h"

class FileBaseClientrMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline FileBaseClientMetaPlugin() {
      pluginList.append(new FileDataBasePlugin);
  }
};

Q_EXPORT_PLUGIN2(FileBaseClientMetaPlugin, FileBaseClientMetaPlugin);

#endif // FILEBASECLIENTMETAPLUGIN_H
