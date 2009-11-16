#include "MainView.h"
#include  "ManageClasses/AdmAddClassWidget.h"
#include	"ManageParents/ManageParents.h"
#include	"ManageStudents/ManageStudents.h"

MainView::MainView(PluginManager *pluginManager)
{
		this->addTab(new AdmAddClassWidget(pluginManager->findPlugin<TreeDataPlugin *>(), pluginManager->findPlugin<UserDataPlugin *>()), QIcon(":/Icons/desk.png"), tr("Classes"));
    this->addTab(new ManageStudents(pluginManager->findPlugin<TreeDataPlugin *>(), pluginManager->findPlugin<UserDataPlugin *>()), QIcon(":/Icons/students.png"), tr("Students"));
        this->addTab(new ManageParents(this, pluginManager), QIcon(":/Icons/parents.png"), tr("Parents"));
}
