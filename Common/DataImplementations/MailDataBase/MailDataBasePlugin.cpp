#include "MailDataBasePlugin.h"
#include "MailDataBase.h"

#include "../../../Common/PluginManager.h"
#include "../../../Common/Plugin.h"

MailDataBasePlugin::MailDataBasePlugin()
{
}

/*
MailData* MailDataBasePlugin::getSettings(QString part, quint8 scope, quint32 ownerId)
{
    foreach (MailData* setting, settings)
        if (setting->part() == part && setting->scope() == scope && setting->owner() == ownerId)
            return setting;

    MailDataBase* set = new MailDataBase(this, part, scope, ownerId);
    settings.append(set);
    return set;
}
*/

Data* MailDataBasePlugin::getDataWithKey(QDataStream& s)
{

}

#ifdef HORUS_SERVER

#endif
