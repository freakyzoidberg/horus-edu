#include <QIcon>

#include "MainView.h"
#include "edtplanning.h"

MainView::MainView(PluginManager *pluginManager)
{
	EdtManager = new ManageEdt(pluginManager);
	EdtSceneView = new EdtWidget(pluginManager);

	this->addTab(EdtSceneView, QIcon(":/Icons/desk.png"), tr("Weekly view"));
	this->addTab(new EdtPlanning(), QIcon(":/Icons/desk.png"), tr("View planning"));

	if (pluginManager->currentUser()->level() <= LEVEL_ADMINISTRATOR)
	{
		this->addTab(EdtManager, QIcon(":/Icons/desk.png"), tr("Manage EDT"));
		this->setTabEnabled(0, false);
		this->setTabEnabled(1, false);
	}
}
