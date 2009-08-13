#ifndef SETTINGSDATAPLUGIN_H
#define SETTINGSDATAPLUGIN_H

#include "DataPlugin.h"

class Data;
class SettingsData;
class SettingsDataPlugin : public DataPlugin
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerDataPlugin)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientDataPlugin)
#endif

public:
    virtual SettingsData* getSettings(QString part = QString(), quint8 scope = 0, quint32 userId = 0) = 0;
};

#ifdef HORUS_SERVER
typedef SettingsDataPlugin ServerSettingsDataPlugin;
Q_DECLARE_INTERFACE(ServerSettingsDataPlugin, "net.horus.ServerSettingsDataPlugin/1.0");
#endif
#ifdef HORUS_CLIENT
typedef SettingsDataPlugin ClientSettingsDataPlugin;
Q_DECLARE_INTERFACE(ClientSettingsDataPlugin, "net.horus.ClientSettingsDataPlugin/1.0");
#endif

#endif // SETTINGSDATAPLUGIN_H
