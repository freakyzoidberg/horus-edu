#ifndef MAILMETAPLUGIN_H
#define MAILMETAPLUGIN_H

#include "../../../../Common/MetaPlugin.h"

#include "Mail.h"

class MailMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline MailMetaPlugin() {
      Plugin* p = new Mail();
      pluginList.append(p);
  }
};

/* maybe put this lines in a cpp if this file is include by an other file */
// declare instance of the plugin
Q_EXPORT_PLUGIN2(MailMetaPlugin, MailMetaPlugin);

#endif // MAILMETAPLUGIN_H
