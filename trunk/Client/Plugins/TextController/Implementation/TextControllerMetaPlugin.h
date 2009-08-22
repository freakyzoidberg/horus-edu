#ifndef TEXTCONTROLLERMETAPLUGIN_H
#define TEXTCONTROLLERMETAPLUGIN_H

#include "../../../../Common/MetaPlugin.h"

#include "TextController.h"

class TextControllerMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline TextControllerMetaPlugin() {
      Plugin* p = new TextController();
      pluginList.append(p);
  }
};

/* maybe put this lines in a cpp if this file is include by an other file */
// declare instance of the plugin
Q_EXPORT_PLUGIN2(TextControllerMetaPlugin, TextControllerMetaPlugin);

#endif // TEXTCONTROLLERMETAPLUGIN_H
