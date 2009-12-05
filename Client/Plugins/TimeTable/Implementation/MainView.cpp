#include <QIcon>

#include "MainView.h"
#include "EdtScene.h"
#include "edtplanning.h"

MainView::MainView(PluginManager *pluginManager)
{
	this->addTab(new EDTScene(pluginManager), QIcon(":/Icons/desk.png"), tr("Weekly view"));

	/*pluginManager->findPlugin<TreeDataPlugin *>(),
								pluginManager->findPlugin<UserDataPlugin *>(),
								pluginManager->findPlugin<ScheduleDataPlugin *>(),
								   QIcon(":/Icons/desk.png"),
								   tr("Classes")) */

	//this->addTab(new ManageEdt(), QIcon(":/Icons/desk.png"), tr("Manage EDT"));

	//this->addTab(new EDTPlanning());

	/*pluginManager->findPlugin<TreeDataPlugin *>(),
								 pluginManager->findPlugin<UserDataPlugin *>()),
								QIcon(":/Icons/students.png"), tr("Students")*/
	/*this->addTab(new ManageTeachers(this, pluginManager), QIcon(":/Icons/teachers.png"), tr("Teachers"));
	this->addTab(new ManageAdministratives(this, pluginManager), QIcon(":/Icons/administrator.png"), tr("Administratives")); */
}
