#ifndef MAILMETAPLUGIN_H
#define MAILMETAPLUGIN_H

#include "../../../../Common/MetaPlugin.h"
#include "../../../../Common/DataImplementations/MailData/MailDataPlugin.h"
#include "Mail.h"
#include "MailSmallDisplayable.h"

class MailMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline MailMetaPlugin() {
      Plugin* p = new Mail();
      Plugin* mp = new MailDataPlugin();
      pluginList.append(p);
      pluginList.append(mp);
	  pluginList.append(new MailSmallDisplayable());
  }
};

/* maybe put this lines in a cpp if this file is include by an other file */
// declare instance of the plugin
Q_EXPORT_PLUGIN2(MailMetaPlugin, MailMetaPlugin);

#endif // MAILMETAPLUGIN_H
