#include "MainFrame.h"

#include <QDebug>

#include "../../../Common/PluginManager.h"
#include "../../../Common/TreeDataPlugin.h"

#include "MainFrameWidget.h"

bool MainFrame::canLoad() const
{
	if (pluginManager->findPlugin<TreeDataPlugin*>())
		return (true);
	return (false);
}

void MainFrame::load()
{
    TreeDataPlugin* t = pluginManager->findPlugin<TreeDataPlugin*>();
    if ( ! t->isLoaded())
        t->load();
    Plugin::load();
}

QWidget* MainFrame::getWidget()
{
    return new MainFrameWidget(this);
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
