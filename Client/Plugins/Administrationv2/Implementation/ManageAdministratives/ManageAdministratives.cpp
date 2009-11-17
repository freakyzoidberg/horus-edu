#include	"ManageAdministratives.h"

ManageAdministratives::ManageAdministratives(QWidget *parent, PluginManager *pluginManager) : QWidget(parent), _pluginManager(pluginManager)
{
	layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
	layout->setSpacing(0);
	layout->setMargin(0);
	list = new ListAdministratives(this, pluginManager);
	layout->addWidget(list);
	connect(list, SIGNAL(editAdministrative(UserData *)), this, SLOT(AdministrativeEdited(UserData *)));
}

void		ManageAdministratives::AdministrativeEdited(UserData *user)
{
	list->hide();
	edit = new EditAdministrative(this, _pluginManager, user);
	layout->addWidget(edit);
	connect(edit, SIGNAL(exit()), this, SLOT(editExited()));
}

void		ManageAdministratives::editExited()
{
	disconnect(edit, SIGNAL(exit()), this, SLOT(editExited()));
	delete edit;
	list->show();
	list->listView->update();
}
