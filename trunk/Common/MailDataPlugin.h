#ifndef MAILDATAPLUGIN_H
#define MAILDATAPLUGIN_H

#include "DataPlugin.h"

class Data;
class MailData;
class MailDataPlugin : public DataPlugin
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerDataPlugin)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientDataPlugin)
#endif

  /*
public:
    virtual MailData* getSettings(QString part = QString(), quint8 scope = 0, quint32 userId = 0) = 0;
    */
};

#ifdef HORUS_SERVER
typedef MailDataPlugin ServerMailDataPlugin;
Q_DECLARE_INTERFACE(ServerMailDataPlugin, "net.horus.ServerMailDataPlugin/1.0");
#endif
#ifdef HORUS_CLIENT
typedef MailDataPlugin ClientMailDataPlugin;
Q_DECLARE_INTERFACE(ClientMailDataPlugin, "net.horus.ClientMailDataPlugin/1.0");
#endif

#endif // MAILDATAPLUGIN_H
