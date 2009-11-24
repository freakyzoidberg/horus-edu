#ifndef SETTINGSDATABASEPLUGIN_H
#define SETTINGSDATABASEPLUGIN_H

#include <QHash>
#include "../../SettingsDataPlugin.h"

class Data;
class SettingsData;
class SettingsDataBase;
class SettingsDataBasePlugin : public SettingsDataPlugin
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerSettingsDataPlugin)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientSettingsDataPlugin)
#endif

public:
	SettingsData*			settings(QString part = QString(), quint8 scope = CLIENT_USER_SCOPE, UserData* user = 0);
	SettingsDataBasePlugin();


	//Plugin
public:
	inline const QString	pluginName() const { return "Settings Data Base"; }
	inline const QString	pluginVersion() const { return "0.1"; }
	void					load();
	void					unload();
	bool					canLoad() const;


	//DataPlugin
protected:
    //! Return the pointer to the Data with a his unique key read in the stream
	Data*					dataWithKey(QDataStream& s);
};

#endif // SETTINGSDATABASEPLUGIN_H
