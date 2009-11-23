#include "MainFrame.h"

#include "../../../Common/PluginManager.h"
#include "../../../Common/TreeDataPlugin.h"
#include "../../../Common/SettingsDataPlugin.h"
#include "MainFrameWidget.h"

bool MainFrame::canLoad() const
{
        if (pluginManager->findPlugin<TreeDataPlugin*>() && pluginManager->findPlugin<SettingsDataPlugin*>())
		return (true);
	return (false);
}

void MainFrame::load()
{
    TreeDataPlugin* t = pluginManager->findPlugin<TreeDataPlugin*>();
    if (!t->isLoaded())
        t->load();
    Plugin::load();
}

QWidget* MainFrame::getWidget()
{
    return (new MainFrameWidget(pluginManager));
}

void MainFrame::courseClicked()
{
    emit switchToWidget(pluginManager->findPlugin<DisplayablePlugin*>("Course")->getWidget());
}

int	MainFrame::getOrder() const
{
	return (-1);
}

QIcon		MainFrame::getIcon() const
{
	return (QIcon(":/Pictures/icon"));
}
