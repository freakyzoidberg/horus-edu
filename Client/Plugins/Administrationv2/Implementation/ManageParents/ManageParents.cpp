#include	"ManageParents.h"

ManageParents::ManageParents(QWidget *parent, PluginManager *pluginManager) : QWidget(parent), _pluginManager(pluginManager)
{
	layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
	layout->setSpacing(0);
	layout->setMargin(0);
	list = new ListParents(this, pluginManager);
	layout->addWidget(list);
        //connect(list, SIGNAL(editParent(UserData *)), this, SLOT(parentEdited(UserData *)));
}

void		ManageParents::parentEdited(UserData *user)
{
//	list->hide();
//	edit = new EditParent(this, _pluginManager, user);
//	layout->addWidget(edit);
//	connect(edit, SIGNAL(exit()), this, SLOT(editExited()));
}

void		ManageParents::editExited()
{
	disconnect(edit, SIGNAL(exit()), this, SLOT(editExited()));
	delete edit;
	list->show();
	list->listView->update();
}
