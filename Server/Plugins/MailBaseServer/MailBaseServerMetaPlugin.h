#ifndef MAILBASESERVERMETAPLUGIN_H
#define MAILBASESERVERMETAPLUGIN_H

#include "../../../Common/MetaPlugin.h"

#include "../../../Common/DataImplementations/MailDataBase/MailDataBasePlugin.h"

class MailBaseServerMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline MailBaseServerMetaPlugin() {
      pluginList.append(new MailDataBasePlugin);
  }
};

Q_EXPORT_PLUGIN2(MailBaseServerMetaPlugin, MailBaseServerMetaPlugin);

#endif // MAILBASESERVERMETAPLUGIN_H
