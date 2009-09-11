#include "Administration.h"
#include "../../../ClientEvents.h"
#include "../../../../Common/PluginManager.h"
#include "../../../../Common/TreeDataPlugin.h"

QEvent::Type ClientEvents::LoadPluginEvent;

QWidget             *Administration::getWidget()
{
    return new AdminMainFrame(this);
}

const QString   Administration::pluginName() const
{
    return ("Administration");
}

const QString   Administration::pluginVersion() const
{
    return ("1.1");
}

const QString   Administration::getDisplayableName()
{
    return "Administration";
}

bool Administration::canLoad() const
{
        if (pluginManager->findPlugin<TreeDataPlugin*>())
                return (true);
        return (false);
}

void Administration::load()
{
    TreeDataPlugin* t = pluginManager->findPlugin<TreeDataPlugin*>();
    if ( ! t->isLoaded())
        t->load();
    Plugin::load();
}
