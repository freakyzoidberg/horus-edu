#include "SettingsDataBasePlugin.h"
#include "SettingsDataBase.h"

#include "../../PluginManager.h"
#include "../../Plugin.h"
#include "../../UserData.h"
#include "../../UserDataPlugin.h"

SettingsDataBasePlugin::SettingsDataBasePlugin()
{
}

SettingsData* SettingsDataBasePlugin::getSettings(QString part, quint8 scope, UserData* user)
{
    if IS_SYSTEM_SCOPE(scope)
        user = pluginManager->findPlugin<UserDataPlugin*>()->getUser(0);
    else if (user == 0)
        user = pluginManager->currentUser();

    foreach (SettingsData* setting, settings)
        if (setting->part() == part && setting->scope() == scope && setting->owner() == user)
            return setting;

    //not found
    SettingsDataBase* set = new SettingsDataBase(this, part, scope, user);
	set->moveToThread(this->thread());
    settings.append(set);
    return set;
}

Data* SettingsDataBasePlugin::getDataWithKey(QDataStream& s)
{
    QString part;
    quint8 scope;
    quint32 ownerId;
    s >> part >> scope >> ownerId;

    return getSettings(part, scope, pluginManager->findPlugin<UserDataPlugin*>()->getUser(ownerId));
}

QList<Data*> SettingsDataBasePlugin::allDatas() const
{
	QList<Data*> list;
	foreach (Data* data, settings)
		if (data->status() != Data::EMPTY)
			list.append(data);

	return list;
}
#ifdef HORUS_SERVER
void SettingsDataBasePlugin::loadData()
{
}

QList<Data*> SettingsDataBasePlugin::datasForUpdate(UserData* user, QDateTime date)
{
	QList<Data*> list;
//    foreach (UserData* data, users)
//        if (data->lastChange() >= date && data->status() == Data::UPTODATE)
//			list.append(data);
	return list;
}
#endif
