#include							"MainFrameWidget.h"

#include							<QApplication>
#include							<QDragEnterEvent>
#include							<QFrame>

#include							"../../../../Common/UserData.h"
#include							"../../../../Common/SettingsData.h"
#include							"../SmallDisplayablePlugin.h"
#include							"DragingWidget.h"

MainFrameWidget::MainFrameWidget(PluginManager *pluginManager) : QWidget()
{
	_pluginManager = pluginManager;
	fillWidgets();
	setStyle();
	setAcceptDrops(true);
	setMouseTracking(true);
	updateInfos();
}

void								MainFrameWidget::fillWidgets()
{
	QList<SmallDisplayablePlugin *>	plugins;
	QBoxLayout						*mainLayout;
	QBoxLayout						*topLayout;
	QBoxLayout						*bottomLayout;
	QBoxLayout						*middleLayout;
	SettingsData					*settings;
	bool							flag;

	plugins = _pluginManager->findPlugins<SmallDisplayablePlugin *>();
	settings = _pluginManager->findPlugin<SettingsDataPlugin *>()->settings("MainBoard");
	empty = 0;
	toDelete = 0;
	mainLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
	topLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	bottomLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	leftLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	middleLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	rightLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	mainLayout->addLayout(topLayout, 0);
	mainLayout->addLayout(bottomLayout, 1);
	bottomLayout->addLayout(leftLayout, 1);
	bottomLayout->addLayout(middleLayout, 0);
	bottomLayout->addLayout(rightLayout, 1);
	middleLayout->addWidget(new QWidget(this), 1);
    connectedAs = new QLabel(tr("Not connected"), this);
    topLayout->addWidget(connectedAs, 1);
    lastLogin = new QLabel(tr("Last login: Never"), this);
    topLayout->addWidget(lastLogin, 1);
	stuff = new QComboBox(this);
	stuff->addItem(tr("Add Stuff..."));
	connect(stuff, SIGNAL(currentIndexChanged(int)), this, SLOT(addedStuff(int)));
	topLayout->addWidget(stuff, 1, Qt::AlignRight);
	foreach (SmallDisplayablePlugin *plugin, plugins)
	{
		flag = false;
		for (int i = 0; i < settings->value("Left Widget Number", 0).toInt(); i++)
			if (settings->value("Left Widget " + QString::number(i)) == plugin->pluginName())
			{
				leftLayout->insertWidget(i, new DragingWidget(this, plugin), 1);
				flag = true;
			}
		for (int i = 0; i < settings->value("Right Widget Number", 0).toInt(); i++)
			if (settings->value("Right Widget " + QString::number(i)) == plugin->pluginName())
			{
				rightLayout->insertWidget(i, new DragingWidget(this, plugin), 1);
				flag = true;
			}
		if (!flag)
			stuff->addItem(plugin->getIcon(), plugin->getDisplayableName(), plugin->pluginName());
	}
}

void								MainFrameWidget::setStyle()
{
	QString							style = ".MainFrameWidget { background-image: url(:/Pictures/HorusPanelBackground-NoFx.png); background-position: center; background-repeat: no-repeat;}";
	setStyleSheet(style);
}

void								MainFrameWidget::updateSettings()
{
	SettingsData					*settings;

	settings = _pluginManager->findPlugin<SettingsDataPlugin *>()->settings("MainBoard");
	settings->setValue("Left Widget Number", QVariant());
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
	QWidget							*inserted;

	if (index <= 0)
		return ;
	inserted = new DragingWidget(this, _pluginManager->findPlugin<SmallDisplayablePlugin *>(stuff->itemData(index).toString()));
	if (leftLayout->count() <= rightLayout->count())
		leftLayout->addWidget(inserted, 1);
	else
		rightLayout->addWidget(inserted, 1);
	inserted->show();
	stuff->setCurrentIndex(0);
	stuff->removeItem(index);
	updateSettings();
}

void								MainFrameWidget::dragEnterEvent(QDragEnterEvent *dragEvent)
{
	bool							noWidget;

	if (dragEvent->mimeData()->hasFormat("application/vnd.horus.whiteboard.widget"))
	{
		dragEvent->acceptProposedAction();
		if (empty == 0)
		{
			foreach (DragingWidget *widget, findChildren<DragingWidget *>())
			{
				if ((leftLayout->indexOf(widget) >=0 || rightLayout->indexOf(widget) >=0) && _pluginManager->findPlugin<SmallDisplayablePlugin *>(dragEvent->mimeData()->data("application/vnd.horus.whiteboard.widget")) == widget->_plugin)
				{
					empty = new QFrame(this);
					empty->setObjectName("Empty");
					if (leftLayout->indexOf(widget) >= 0)
					{
						leftLayout->insertWidget(leftLayout->indexOf(widget), empty, 1);
						leftLayout->removeWidget(widget);
					}
					else
					{
						rightLayout->insertWidget(rightLayout->indexOf(widget), empty, 1);
						rightLayout->removeWidget(widget);
					}
					toDelete = widget;
					widget->hide();
					empty->show();
					break ;
				}
			}
		}
		noWidget = true;
		foreach (DragingWidget *widget, findChildren<DragingWidget *>())
		{
			if ((leftLayout->indexOf(widget) >=0 || rightLayout->indexOf(widget) >=0) && widget->geometry().contains(dragEvent->pos()))
			{
				int				oldIndex;

				noWidget = false;
				oldIndex = leftLayout->indexOf(empty);
				if (oldIndex >= 0)
					leftLayout->removeWidget(empty);
				else
				{
					oldIndex = rightLayout->indexOf(empty);
					rightLayout->removeWidget(empty);
				}
				if (leftLayout->indexOf(widget) >= 0)
					leftLayout->insertWidget(leftLayout->indexOf(widget) + (leftLayout->indexOf(widget) >= oldIndex ? 1 : 0), empty, 1);
				else
					rightLayout->insertWidget(rightLayout->indexOf(widget) + (rightLayout->indexOf(widget) >= oldIndex ? 1 : 0), empty, 1);
			}
		}
		if (noWidget && !empty->geometry().contains(dragEvent->pos()))
		{
			QRect left(geometry().left(), geometry().top(), geometry().width() / 2, geometry().height());
			QRect right(geometry().left() + geometry().width() / 2, geometry().top(), geometry().width() / 2, geometry().height());
			if (left.contains(dragEvent->pos()) && !leftLayout->count())
			{
				rightLayout->removeWidget(empty);
				leftLayout->insertWidget(0, empty, 1);
			}
			else if (right.contains(dragEvent->pos()) && !rightLayout->count())
			{
				leftLayout->removeWidget(empty);
				rightLayout->insertWidget(0, empty, 1);
			}
		}
	}
}

void								MainFrameWidget::dropEvent(QDropEvent *dropEvent)
{
	QWidget							*inserted;

	if (empty)
	{
		inserted = new DragingWidget(this, _pluginManager->findPlugin<SmallDisplayablePlugin *>(dropEvent->mimeData()->data("application/vnd.horus.whiteboard.widget")));
		if (leftLayout->indexOf(empty) >= 0)
		{
			leftLayout->insertWidget(leftLayout->indexOf(empty), inserted, 1);
			leftLayout->removeWidget(empty);
		}
		else
		{
			rightLayout->insertWidget(rightLayout->indexOf(empty), inserted, 1);
			rightLayout->removeWidget(empty);
		}
		empty->hide();
		inserted->show();
		//delete empty;
		empty = 0;
		updateSettings();
	}
}

void							MainFrameWidget::mouseMoveEvent(QMouseEvent *mouseEvent)
{
	if (mouseEvent->buttons())
	{
		mouseEvent->ignore();
		return ;
	}
	if (toDelete)
	{
		//delete toDelete;
		toDelete = 0;
	}
	//foreach (DragingWidget *widget, findChildren<DragingWidget *>())
	//	if (!widget->isVisible())
	//		delete widget;
	if (empty)
	{
		empty->hide();
		//delete empty;
		empty = 0;
		repopulateStuff();
	}
	mouseEvent->ignore();
}

void							MainFrameWidget::repopulateStuff()
{
	QList<SmallDisplayablePlugin *>	plugins;

	plugins = _pluginManager->findPlugins<SmallDisplayablePlugin *>();
	foreach (DragingWidget *widget, findChildren<DragingWidget *>())
		if (plugins.contains(widget->_plugin) && widget->isVisible())
			plugins.removeAll(widget->_plugin);
	foreach (SmallDisplayablePlugin *plugin, plugins)
		if (stuff->findData(plugin->pluginName()) < 0)
			stuff->addItem(plugin->getIcon(), plugin->getDisplayableName(), plugin->pluginName());
	updateSettings();
}
