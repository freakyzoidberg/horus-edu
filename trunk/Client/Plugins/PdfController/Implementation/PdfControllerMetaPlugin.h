#ifndef PDFCONTROLLERMETAPLUGIN_H
#define PDFCONTROLLERMETAPLUGIN_H

#include "../../../../Common/MetaPlugin.h"

#include "PdfController.h"

class PdfControllerMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline PdfControllerMetaPlugin() {
      Plugin* p = new PdfController();
      pluginList.append(p);
  }
};

/* maybe put this lines in a cpp if this file is include by an other file */
// declare instance of the plugin
Q_EXPORT_PLUGIN2(PdfControllerMetaPlugin, PdfControllerMetaPlugin);

#endif // PDFCONTROLLERMETAPLUGIN_H
