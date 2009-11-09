#ifndef SETTINGSDATAPLUGIN_H
#define SETTINGSDATAPLUGIN_H

#include "DataPlugin.h"

// There is 2 params in a scope.
// If the setting is a value for the user or the system value
#define USER_SCOPE 0
#define SYSTEM_SCOPE 1
// If the setting is on the client or on the server side
#define CLIENT_SCOPE 0
#define SERVER_SCOPE 2

// So, use these values combining the 2 params
#define  CLIENT_USER_SCOPE  (CLIENT_SCOPE |  USER_SCOPE ) // = 00 = 0
#define  SERVER_USER_SCOPE  (SERVER_SCOPE |  USER_SCOPE ) // = 01 = 1
#define CLIENT_SYSTEM_SCOPE (CLIENT_SCOPE | SYSTEM_SCOPE) // = 10 = 2
#define SERVER_SYSTEM_SCOPE (SERVER_SCOPE | SYSTEM_SCOPE) // = 11 = 3

// And for a clean and optimised code, please use theses macro.
#define IS_CLIENT_SCOPE(scope)  ((scope & CLIENT_SCOPE) == CLIENT_SCOPE)
#define IS_SERVER_SCOPE(scope)  ((scope & SERVER_SCOPE) == SERVER_SCOPE)
#define IS_SYSTEM_SCOPE(scope)  ((scope & SYSTEM_SCOPE) == SYSTEM_SCOPE)
#define IS_USER_SCOPE(scope)    ((scope &  USER_SCOPE ) ==  USER_SCOPE )

class Data;
class UserData;
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
	inline const QString dataType() const { return "Settings"; }

  virtual SettingsData* settings(QString part = QString(), quint8 scope = CLIENT_USER_SCOPE, UserData* user = 0) = 0;
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
