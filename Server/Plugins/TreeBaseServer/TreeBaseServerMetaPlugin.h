#ifndef TREEBASESERVERMETAPLUGIN_H
#define TREEBASESERVERMETAPLUGIN_H

#include "../../../Common/MetaPlugin.h"

#include "../../../Common/DataImplementations/TreeDataBase/TreeDataBasePlugin.h"

class TreeBaseServerMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline TreeBaseServerMetaPlugin() {
      pluginList.append(new TreeDataBasePlugin);
  }
};

/* maybe put this lines in a cpp if this file is include by an other file */
// declare instance of the plugin
Q_EXPORT_PLUGIN2(TreeBaseServerMetaPlugin, TreeBaseServerMetaPlugin);

#endif // TREEBASESERVERMETAPLUGIN_H
