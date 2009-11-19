#include "SettingsDataBasePlugin.h"
#include "SettingsDataBase.h"

#include "../../PluginManager.h"
#include "../../Plugin.h"
#include "../../UserData.h"
#include "../../UserDataPlugin.h"

SettingsDataBasePlugin::SettingsDataBasePlugin()
{
}

SettingsData* SettingsDataBasePlugin::settings(QString part, quint8 scope, UserData* user)
{
    if IS_SYSTEM_SCOPE(scope)
		user = pluginManager->findPlugin<UserDataPlugin*>()->nobody();
    else if (user == 0)
        user = pluginManager->currentUser();

	foreach (SettingsData* setting, _settings)
        if (setting->part() == part && setting->scope() == scope && setting->owner() == user)
            return setting;

    //not found
    SettingsDataBase* set = new SettingsDataBase(this, part, scope, user);
	set->moveToThread(this->thread());
	_settings.append(set);
    return set;
}

Data* SettingsDataBasePlugin::dataWithKey(QDataStream& s)
{
    QString part;
    quint8 scope;
    quint32 ownerId;
    s >> part >> scope >> ownerId;

	return settings(part, scope, pluginManager->findPlugin<UserDataPlugin*>()->user(ownerId));
}

QList<Data*> SettingsDataBasePlugin::allDatas() const
{
	QList<Data*> list;
	foreach (Data* data, _settings)
		if (data->status() != Data::EMPTY)
			list.append(data);

	return list;
}
#ifdef HORUS_SERVER
void SettingsDataBasePlugin::loadData()
{
	QSqlQuery query = pluginManager->sqlQuery();
	query.prepare("SELECT user,part,scope,value,mtime FROM settings;");

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return;
	}
	UserDataPlugin* userPlugin = pluginManager->findPlugin<UserDataPlugin*>();
	while (query.next())
	{
		SettingsDataBase* s = (SettingsDataBase*)(settings( query.value(1).toString(), //plugin
															query.value(2).toUInt(),	// scope
															userPlugin->user(query.value(0).toUInt()))); //user
		s->_values = query.value(3).toHash();
		s->_lastChange = query.value(4).toDateTime();
		s->_status = Data::UPTODATE;
	}
}

QList<Data*> SettingsDataBasePlugin::datasForUpdate(UserData* user, QDateTime date)
{
	QList<Data*> list;
	foreach (SettingsData* data, _settings)
		if (data->lastChange() >= date && data->status() == Data::UPTODATE)
			list.append(data);
	return list;
}
#endif
