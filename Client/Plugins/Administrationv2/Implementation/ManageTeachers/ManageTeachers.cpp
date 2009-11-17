#include	"ManageTeachers.h"

ManageTeachers::ManageTeachers(QWidget *parent, PluginManager *pluginManager) : QWidget(parent), _pluginManager(pluginManager)
{
	layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
	layout->setSpacing(0);
	layout->setMargin(0);
	list = new ListTeachers(this, pluginManager);
	layout->addWidget(list);
	connect(list, SIGNAL(editTeacher(UserData *)), this, SLOT(TeacherEdited(UserData *)));
}

void		ManageTeachers::TeacherEdited(UserData *user)
{
	list->hide();
	edit = new EditTeacher(this, _pluginManager, user);
	layout->addWidget(edit);
	connect(edit, SIGNAL(exit()), this, SLOT(editExited()));
}

void		ManageTeachers::editExited()
{
	disconnect(edit, SIGNAL(exit()), this, SLOT(editExited()));
	delete edit;
	list->show();
	list->listView->update();
}
