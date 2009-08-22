#ifndef PDFEDITORMETAPLUGIN_H
#define PDFEDITORMETAPLUGIN_H

#include "../../../../Common/MetaPlugin.h"

#include "PdfEditor.h"

class PdfEditorMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline PdfEditorMetaPlugin() {
      Plugin* p = new PdfEditor();
      pluginList.append(p);
  }
};

/* maybe put this lines in a cpp if this file is include by an other file */
// declare instance of the plugin
Q_EXPORT_PLUGIN2(PdfEditorMetaPlugin, PdfEditorMetaPlugin);

#endif // PDFEDITORMETAPLUGIN_H
