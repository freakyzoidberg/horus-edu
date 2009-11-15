#include "MainView.h"
#include  "ManageClasses/AdmAddClassWidget.h"
#include	"ManageParents/ManageParents.h"
#include	"ManageStudents/ManageStudents.h"

MainView::MainView(PluginManager *pluginManager)
{
	this->addTab(new AdmAddClassWidget(pluginManager->findPlugin<TreeDataPlugin *>(), pluginManager->findPlugin<UserDataPlugin *>()), tr("Classrooms"));
    this->addTab(new ManageStudents(treeplugin, userplugin),tr("Students"));
	this->addTab(new ManageParents(this, pluginManager), tr("Parents"));
}
