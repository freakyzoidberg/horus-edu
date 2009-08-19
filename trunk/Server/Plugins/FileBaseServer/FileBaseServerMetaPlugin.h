#ifndef FILEBASESERVERMETAPLUGIN_H
#define FILEBASESERVERMETAPLUGIN_H

#include "../../../Common/MetaPlugin.h"

#include "../../../Common/DataImplementations/FileDataBase/FileDataBasePlugin.h"

class FileBaseServerMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline FileBaseServerMetaPlugin() {
      pluginList.append(new FileDataBasePlugin);
  }
};

/* maybe put this lines in a cpp if this file is include by an other file */
// declare instance of the plugin
Q_EXPORT_PLUGIN2(FileBaseServerMetaPlugin, FileBaseServerMetaPlugin);

#endif // FILEBASESERVERMETAPLUGIN_H
