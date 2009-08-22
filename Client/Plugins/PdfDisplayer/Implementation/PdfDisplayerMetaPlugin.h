#ifndef PDFDISPLAYERMETAPLUGIN_H
#define PDFDISPLAYERMETAPLUGIN_H

#include "../../../../Common/MetaPlugin.h"

#include "PdfDisplayer.h"

class PdfDisplayerMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline PdfDisplayerMetaPlugin() {
      Plugin* p = new PdfDisplayer();
      pluginList.append(p);
  }
};

/* maybe put this lines in a cpp if this file is include by an other file */
// declare instance of the plugin
Q_EXPORT_PLUGIN2(PdfDisplayerMetaPlugin, PdfDisplayerMetaPlugin);

#endif // PDFDISPLAYERMETAPLUGIN_H
