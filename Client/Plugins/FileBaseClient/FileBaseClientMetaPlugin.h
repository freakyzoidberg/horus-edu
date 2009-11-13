#ifndef FILEBASECLIENTMETAPLUGIN_H
#define FILEBASECLIENTMETAPLUGIN_H

#include "../../../Common/MetaPlugin.h"

#include "../../../Common/DataImplementations/FileDataBase/FileDataBasePlugin.h"
#include "FileNetworkPlugin.h"
#include "LibraryPlugin.h"
#include "TransfertPlugin.h"
#include "LibrarySmallDisplayable.h"
#include "DownloadSmallDisplayable.h"

class FileBaseClientMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline FileBaseClientMetaPlugin() {
	  FileDataBasePlugin* filePlugin = new FileDataBasePlugin;
	  pluginList.append( filePlugin);
	  pluginList.append( new FileNetworkPlugin(filePlugin) );
	  pluginList.append( new LibraryPlugin );
	  pluginList.append( new LibrarySmallDisplayable );
	  pluginList.append( new DownloadSmallDisplayable );
//          pluginList.append( new TransfertPlugin );
  }
};

Q_EXPORT_PLUGIN2(FileBaseClientMetaPlugin, FileBaseClientMetaPlugin);

#endif // FILEBASECLIENTMETAPLUGIN_H
