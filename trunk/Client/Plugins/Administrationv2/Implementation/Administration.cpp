#include "Administration.h"

#include <QLabel>

#include "../../../../Common/PluginManager.h"
#include "../../../../Common/TreeDataPlugin.h"
#include "../../../../Common/UserData.h"
#include "../../../../Common/EventData.h"
#include "MainView.h"
QWidget             *Administration::getWidget()
{
    UserData* u = pluginManager->currentUser();
    if (u != 0)
        if (u->level() > LEVEL_ADMINISTRATOR)
            return NULL;
    return new MainView(pluginManager);
}

const QString   Administration::pluginName() const
{
    return ("Administrationv2");
}

const QString   Administration::pluginVersion() const
{
    return ("1.1");
}

const QString   Administration::getDisplayableName() const
{
    return "Administration";
}

bool Administration::canLoad() const
{
    if (pluginManager->findPlugin<TreeDataPlugin*>() && pluginManager->findPlugin<UserDataPlugin *>() && pluginManager->findPlugin<EventDataPlugin *>())
                return (true);
        return (false);
}

int Administration::getOrder() const
{
    return 42;
}
QIcon   Administration::getIcon() const
{
    return (QIcon(":/images/admin.png"));
}
