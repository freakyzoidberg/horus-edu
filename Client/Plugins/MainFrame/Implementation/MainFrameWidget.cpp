#include							"MainFrameWidget.h"

#include							<QApplication>

#include							"../../../../Common/UserData.h"
#include							"../../../../Common/SettingsData.h"
#include							"../SmallDisplayablePlugin.h"

MainFrameWidget::MainFrameWidget(PluginManager *pluginManager) : QWidget()
{
	_pluginManager = pluginManager;
	fillWidgets();
	setStyle();
	updateInfos();
}

void								MainFrameWidget::fillWidgets()
{
	QList<SmallDisplayablePlugin *>	plugins;
	QBoxLayout						*mainLayout;
	QBoxLayout						*topLayout;
	QBoxLayout						*bottomLayout;
	SettingsData					*settings;
	bool							flag;

	plugins = _pluginManager->findPlugins<SmallDisplayablePlugin *>();
	settings = _pluginManager->findPlugin<SettingsDataPlugin *>()->settings("MainBoard");
	mainLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
	topLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	bottomLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	leftLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	rightLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	mainLayout->addLayout(topLayout, 0);
	mainLayout->addLayout(bottomLayout, 1);
	bottomLayout->addLayout(leftLayout, 1);
	bottomLayout->addLayout(rightLayout, 1);
    connectedAs = new QLabel(tr("Not connected"), this);
    topLayout->addWidget(connectedAs, 1);
    lastLogin = new QLabel(tr("Last login: Never"), this);
    topLayout->addWidget(lastLogin, 1);
	stuff = new QComboBox(this);
	stuff->addItem(tr("Add Stuff..."));
	connect(stuff, SIGNAL(currentIndexChanged(int)), this, SLOT(addedStuff(int)));
	topLayout->addWidget(stuff, 1, Qt::AlignRight);
	leftLayout->addWidget(new QLabel("Left layout 1", this), 1);
	leftLayout->addWidget(new QLabel("Left layout 2", this), 1);
	leftLayout->addWidget(new QLabel("Left layout 3", this), 1);
	rightLayout->addWidget(new QLabel("Right layout 1", this), 1);
	rightLayout->addWidget(new QLabel("Right layout 2", this), 1);
	foreach (SmallDisplayablePlugin *plugin, plugins)
	{
		flag = false;
		for (int i = 0; i < settings->value("Left Widget Number", 0).toInt(); i++)
			if (settings->value("Left Widget " + QString::number(i)) == plugin->pluginName())
			{
				leftLayout->insertWidget(i, plugin->getWidget(), 1); // TODO put embedded widget
				flag = true;
			}
		for (int i = 0; i < settings->value("Right Widget Number", 0).toInt(); i++)
			if (settings->value("Right Widget " + QString::number(i)) == plugin->pluginName())
			{
				leftLayout->insertWidget(i, plugin->getWidget(), 1); // TODO put embedded widget
				flag = true;
			}
		if (!flag)
			stuff->addItem(plugin->getIcon(), plugin->getDisplayableName(), plugin->pluginName());
	}
}

void								MainFrameWidget::setStyle()
{
	QString							style = "QWidget{border:1px solid red}.MainFrameWidget { background-image: url(:/Pictures/HorusPanelBackground-NoFx.png); background-position: center; background-repeat: non;}";
	setStyleSheet(style);
}

void								MainFrameWidget::updateSettings()
{
}

void								MainFrameWidget::updateInfos()
{
    UserData*						user;

	user = _pluginManager->currentUser();
    if (!user)
        return ;
    disconnect(user, SIGNAL(updated()), this, SLOT(updateInfos()));
    connect(user, SIGNAL(updated()), this, SLOT(updateInfos()));
    connectedAs->setText(tr("Connected as: ") + user->login() + tr(" (") + user->name() + tr(" ") + user->surname() + tr(")"));
    if (user->lastLogin().isValid())
        lastLogin->setText(tr("Last login: ") + user->lastLogin().toString());
    else
        lastLogin->setText(tr("Last login: Never"));
}

void								MainFrameWidget::addedStuff(int index)
{
	QWidget							*widget;

	if (index <= 0)
		return ;
	widget = _pluginManager->findPlugin<SmallDisplayablePlugin *>(stuff->itemData(index).toString())->getWidget();
	stuff->removeItem(index);
	stuff->setCurrentIndex(0);
	if (leftLayout->count() <= rightLayout->count())
		leftLayout->addWidget(widget, 1);
	else
		rightLayout->addWidget(widget, 1);
	updateSettings();
}
