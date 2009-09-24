#ifndef WHITEBOARDDATASERVERMETAPLUGIN_H
#define WHITEBOARDDATASERVERMETAPLUGIN_H

#include "../../../Common/MetaPlugin.h"

#include "../../../Common/DataImplementations/WhiteBoardData/WhiteBoardDataPlugin.h"

class WhiteBoardDataServerMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
	inline WhiteBoardDataServerMetaPlugin() {
	  pluginList.append(new WhiteBoardDataPlugin);
  }
};

Q_EXPORT_PLUGIN2(WhiteBoardDataServerMetaPlugin, WhiteBoardDataServerMetaPlugin);

#endif // WHITEBOARDDATASERVERMETAPLUGIN_H
