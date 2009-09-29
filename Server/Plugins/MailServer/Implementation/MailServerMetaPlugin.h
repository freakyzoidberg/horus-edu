#ifndef MAILSERVERMETAPLUGIN_H
#define MAILSERVERMETAPLUGIN_H

#include "../../../../Common/MetaPlugin.h"

#include "../../../../Common/DataImplementations/MailData/MailDataPlugin.h"

class MailServerMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline MailServerMetaPlugin() {
      pluginList.append(new MailDataPlugin);
  }
};

/* maybe put this lines in a cpp if this file is include by an other file */
// declare instance of the plugin
Q_EXPORT_PLUGIN2(MailServerMetaPlugin, MailServerMetaPlugin);

#endif // MAILSERVERMETAPLUGIN_H
