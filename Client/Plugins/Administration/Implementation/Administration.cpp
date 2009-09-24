#include "Administration.h"
#include "../../../ClientEvents.h"
#include "../../../../Common/PluginManager.h"
#include "../../../../Common/TreeDataPlugin.h"

QEvent::Type ClientEvents::LoadPluginEvent;

QWidget             *Administration::getWidget()
{
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

const int Administration::getOrder() const
{
    return 42;
}
