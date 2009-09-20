#ifndef MEDIACONTROLLERMETAPLUGIN_H
#define MEDIACONTROLLERMETAPLUGIN_H

#include "../../../../Common/MetaPlugin.h"

#include "AudioController.h"

class AudioControllerMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline AudioControllerMetaPlugin() {
      Plugin* p = new AudioController();
      pluginList.append(p);
  }
};

/* maybe put this lines in a cpp if this file is include by an other file */
// declare instance of the plugin
Q_EXPORT_PLUGIN2(AudioControllerMetaPlugin, AudioControllerMetaPlugin);

#endif // PDFCONTROLLERMETAPLUGIN_H
