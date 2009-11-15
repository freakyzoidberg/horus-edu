#include		"ManageParents.h"

#include		<QBoxLayout>
#include		<QListView>
#include		<QFrame>
#include		<QLabel>

#include		"../../../../../Common/PluginManager.h"
#include		"DisplayParent.h"

ManageParents::ManageParents(QWidget *parent, PluginManager *pluginManager) : QWidget(parent), _pluginManager(pluginManager)
{
	QBoxLayout	*mainLayout;
	QBoxLayout	*rightLayout;
	QBoxLayout	*informationsLayout;
	QListView	*listView;
	QFrame		*informationsFrame;
	QFrame		*actionsFrame;
	QLabel		*informationsTitle;

	mainLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
	listView = new QListView(this);
	mainLayout->addWidget(listView);
	rightLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	informationsFrame = new QFrame(this);
	informationsLayout = new QBoxLayout(QBoxLayout::TopToBottom, informationsFrame);
	informationsTitle = new QLabel(this);
	informationsLayout->addWidget(informationsTitle);
	informationsLayout->addWidget(new DisplayParent(this));
	rightLayout->addWidget(informationsFrame);
	mainLayout->addLayout(rightLayout);
}
