#ifndef IMAGECONTROLLERMETAPLUGIN_H
#define IMAGECONTROLLERMETAPLUGIN_H

#include "../../../../Common/MetaPlugin.h"

#include "ImageController.h"

class ImageControllerMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline ImageControllerMetaPlugin() {
      Plugin* p = new ImageController();
      pluginList.append(p);
  }
};

/* maybe put this lines in a cpp if this file is include by an other file */
// declare instance of the plugin
Q_EXPORT_PLUGIN2(ImageControllerMetaPlugin, ImageControllerMetaPlugin);

#endif // IMAGECONTROLLERMETAPLUGIN_H
