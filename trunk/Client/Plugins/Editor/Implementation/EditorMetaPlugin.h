#ifndef EDITORMETAPLUGIN_H
#define EDITORMETAPLUGIN_H

#include "../../../../Common/MetaPlugin.h"

#include "Editor.h"

class EditorMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline EditorMetaPlugin() {
      Plugin* p = new Editor();
      pluginList.append(p);
  }
};

/* maybe put this lines in a cpp if this file is include by an other file */
// declare instance of the plugin
Q_EXPORT_PLUGIN2(EditorMetaPlugin, EditorMetaPlugin);

#endif // EDITORMETAPLUGIN_H
