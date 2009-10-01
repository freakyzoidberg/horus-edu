#include "Administration.h"
#include "../../../ClientEvents.h"
#include "../../../../Common/PluginManager.h"
#include "../../../../Common/TreeDataPlugin.h"

QEvent::Type ClientEvents::LoadPluginEvent;

QWidget             *Administration::getWidget()
{
    UserData* u = pluginManager->currentUser();
    if (u->level() > 1)
        return new QLabel(tr("Permission denied"));
    return new AdminMainFrame(treePlugin, userPlugin);
}

const QString   Administration::pluginName() const
{
    return ("Administration");
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
    if (pluginManager->findPlugin<TreeDataPlugin*>() && pluginManager->findPlugin<UserDataPlugin *>())
                return (true);
        return (false);
}

void Administration::load()
{
    treePlugin = pluginManager->findPlugin<TreeDataPlugin*>();
    userPlugin = pluginManager->findPlugin<UserDataPlugin *>();

    Plugin::load();
}

int Administration::getOrder() const
{
    return 42;
}
QIcon   Administration::getIcon() const
{
    return (QIcon(":/images/admin.png"));
}
