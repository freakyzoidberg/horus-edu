#include "SettingsDataBasePlugin.h"
#include "SettingsDataBase.h"

#include "../../../Common/PluginManager.h"
#include "../../../Common/Plugin.h"

SettingsDataBasePlugin::SettingsDataBasePlugin()
{
}

SettingsData* SettingsDataBasePlugin::getSettings(QString part, quint8 scope, quint32 ownerId)
{
    foreach (SettingsData* setting, settings)
        if (setting->part() == part && setting->scope() == scope && setting->owner() == ownerId)
            return setting;

    SettingsDataBase* set = new SettingsDataBase(this, part, scope, ownerId);
    settings.append(set);
    return set;
}

Data* SettingsDataBasePlugin::getDataWithKey(QDataStream& s)
{
    QString part;
    quint8 scope;
    quint32 ownerId;
    s >> part >> scope >> ownerId;
    return getSettings(part, scope, ownerId);
}

#ifdef HORUS_SERVER
bool SettingsDataBasePlugin::verifyDataBase(QSqlQuery& TODO)
{
    return true;
}
#endif
