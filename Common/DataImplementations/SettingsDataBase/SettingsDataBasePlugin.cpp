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

#ifdef HORUS_SERVER
void SettingsDataBasePlugin::loadData()
{
}

void SettingsDataBasePlugin::userConnected(UserData* user, QDateTime date)
{
//    foreach (UserData* data, users)
//        if (data->lastChange() >= date && data->status() == Data::UPTODATE)
//            dataManager->sendData(user, data);
}
#endif
