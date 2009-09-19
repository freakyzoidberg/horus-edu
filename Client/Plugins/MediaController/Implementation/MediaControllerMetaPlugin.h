#ifndef MEDIACONTROLLERMETAPLUGIN_H
#define MEDIACONTROLLERMETAPLUGIN_H

#include "../../../../Common/MetaPlugin.h"

#include "mediacontroller.h"

class MediaControllerMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline MediaControllerMetaPlugin() {
      Plugin* p = new MediaController();
      pluginList.append(p);
  }
};

/* maybe put this lines in a cpp if this file is include by an other file */
// declare instance of the plugin
Q_EXPORT_PLUGIN2(MediaControllerMetaPlugin, MediaControllerMetaPlugin);

#endif // PDFCONTROLLERMETAPLUGIN_H
