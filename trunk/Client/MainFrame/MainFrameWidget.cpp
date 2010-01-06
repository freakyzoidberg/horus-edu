/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include							"MainFrameWidget.h"

#include							<QApplication>
#include							<QDragEnterEvent>
#include							<QFrame>
#include <QPushButton>
#include <QGridLayout>
#include			<QBoxLayout>
#include			<QLabel>
#include			<QComboBox>

#include			"../../Common/PluginManager.h"
#include							"../../Common/UserData.h"
#include							"../../Common/SettingsData.h"
#include							"../SmallDisplayablePlugin.h"
#include							"DragingWidget.h"
#include "../NetworkManager.h"

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
	QGridLayout						*mainLayout;
	QHBoxLayout						*topLayout;
	SettingsData					*settings;
	bool							flag;

	plugins = _pluginManager->findPlugins<SmallDisplayablePlugin *>();
	settings = _pluginManager->findPlugin<SettingsDataPlugin *>()->settings("MainBoard");
	empty = new QFrame(this);
	empty->setAcceptDrops(true);
	empty->setObjectName("Empty");
	empty->hide();
	hasEmpty = false;

	mainLayout = new QGridLayout(this);
	topLayout = new QHBoxLayout;
	leftLayout = new QVBoxLayout;
	rightLayout = new QVBoxLayout;
	mainLayout->addLayout(topLayout, 0, 0, 1, 2);
	mainLayout->addLayout(leftLayout, 1, 0, 2, 1);
	mainLayout->addLayout(rightLayout, 1, 1, 1, 1);
	connectedAs = new QLabel(tr("Not connected"), this);
    topLayout->addWidget(connectedAs, 1);
    lastLogin = new QLabel(tr("Last login: Never"), this);
	topLayout->addWidget(lastLogin);
	connexionStatus = new QLabel(this);
	topLayout->addWidget(connexionStatus);
	connect(NetworkManager::instance(), SIGNAL(statusChange(NetworkManager::Status)), this, SLOT(networkStatusChange(NetworkManager::Status)));
	networkStatusChange(NetworkManager::instance()->status());
	QPushButton* logout = new QPushButton(QIcon(":/Pictures/logout.png"), tr("Logout"), this);
	connect(logout, SIGNAL(clicked()), NetworkManager::instance(), SLOT(logout()));
	topLayout->addWidget(logout);
	stuff = new QComboBox(this);
	stuff->addItem(tr("Add Stuff..."));
	connect(stuff, SIGNAL(currentIndexChanged(int)), this, SLOT(addedStuff(int)));
	mainLayout->addWidget(stuff, 2, 1, 1, 1);
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
	connect(_pluginManager->findPlugin<SettingsDataPlugin *>()->settings("MainBoard"), SIGNAL(updated()), this, SLOT(repopulateStuff()));
}

void								MainFrameWidget::setStyle()
{
	QString							style = ".MainFrameWidget { background-image: url(:/Pictures/HorusPanelBackground-NoFx.png); background-position: center; background-repeat: no-repeat;}";
	setStyleSheet(style);
}

void								MainFrameWidget::updateSettings()
{
	SettingsData					*settings;
	int								nbWidget;
	int								nbDragingWidget;

	settings = _pluginManager->findPlugin<SettingsDataPlugin *>()->settings("MainBoard");
	for (nbWidget = 0, nbDragingWidget = 0; nbWidget < leftLayout->count(); nbWidget++)
		if (qobject_cast<DragingWidget *>(leftLayout->itemAt(nbWidget)->widget()))
		{
			settings->setValue("Left Widget " + QString::number(nbDragingWidget), QVariant(qobject_cast<DragingWidget *>(leftLayout->itemAt(nbWidget)->widget())->_plugin->pluginName()));
			++nbDragingWidget;
		}
	settings->setValue("Left Widget Number", QVariant(nbDragingWidget));
	for (nbWidget = 0, nbDragingWidget = 0; nbWidget < rightLayout->count(); nbWidget++)
		if (qobject_cast<DragingWidget *>(rightLayout->itemAt(nbWidget)->widget()))
		{
			settings->setValue("Right Widget " + QString::number(nbDragingWidget), QVariant(qobject_cast<DragingWidget *>(rightLayout->itemAt(nbWidget)->widget())->_plugin->pluginName()));
			++nbDragingWidget;
		}
	settings->setValue("Right Widget Number", QVariant(nbDragingWidget));
	settings->save();
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

	if (dragEvent->mimeData()->hasFormat("x-horus/x-minidisplayable"))
	{
		dragEvent->acceptProposedAction();
		if (!hasEmpty)
		{ // Create the 'empty' widget if not present (the dotted area)
			foreach (DragingWidget *widget, findChildren<DragingWidget *>())
			{
				if ((leftLayout->indexOf(widget) >=0 || rightLayout->indexOf(widget) >=0) && _pluginManager->findPlugin<SmallDisplayablePlugin *>(dragEvent->mimeData()->data("x-horus/x-minidisplayable")) == widget->_plugin)
				{
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

					widget->hide();
					empty->show();
					hasEmpty = true;
					break ;
				}
			}
		}
		noWidget = true;
		foreach (DragingWidget *widget, findChildren<DragingWidget *>())
		{ // Move the 'empty' widget at the place of the current widget under the mouse
			if ((leftLayout->indexOf(widget) >=0 || rightLayout->indexOf(widget) >=0) && widget->geometry().contains(dragEvent->pos()))
			{
				int				oldIndex;
				QRect			top;

				noWidget = false;
				if (leftLayout->indexOf(empty) >= 0)
				{
					if (leftLayout->indexOf(widget) >= 0)
						oldIndex = leftLayout->indexOf(empty);
					else
					{
						top.setRect(widget->geometry().left(), widget->geometry().top(), widget->geometry().width(), widget->geometry().height() * (rightLayout->count() - rightLayout->indexOf(widget)) / (1 + rightLayout->count()));
						if (top.contains(dragEvent->pos()))
							oldIndex = rightLayout->count();
						else
							oldIndex = -1;
					}
					leftLayout->removeWidget(empty);
				}
				else
				{
					if (rightLayout->indexOf(widget) >= 0)
						oldIndex = rightLayout->indexOf(empty);
					else
					{
						top.setRect(widget->geometry().left(), widget->geometry().top(), widget->geometry().width(), widget->geometry().height() * (leftLayout->count() - leftLayout->indexOf(widget)) / (1 + leftLayout->count()));
						if (top.contains(dragEvent->pos()))
							oldIndex = leftLayout->count();
						else
							oldIndex = -1;
					}
					rightLayout->removeWidget(empty);
				}
				if (leftLayout->indexOf(widget) >= 0)
					leftLayout->insertWidget(leftLayout->indexOf(widget) + (leftLayout->indexOf(widget) >= oldIndex ? 1 : 0), empty, 1);
				else
					rightLayout->insertWidget(rightLayout->indexOf(widget) + (rightLayout->indexOf(widget) >= oldIndex ? 1 : 0), empty, 1);
			}
		}
		if (noWidget && !empty->geometry().contains(dragEvent->pos()))
		{ // When no widget under the mouse (mainframe empty)
			QRect left(geometry().left(), geometry().top(), geometry().width() / 2 + 3, geometry().height());
			QRect right(geometry().left() + geometry().width() / 2 - 3, geometry().top(), geometry().width() / 2 + 3, geometry().height());
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

	if (hasEmpty)
	{
		inserted = new DragingWidget(this, _pluginManager->findPlugin<SmallDisplayablePlugin *>(dropEvent->mimeData()->data("x-horus/x-minidisplayable")));
		if (leftLayout->indexOf(empty) >= 0)
			leftLayout->insertWidget(leftLayout->indexOf(empty), inserted, 1);
		else
			rightLayout->insertWidget(rightLayout->indexOf(empty), inserted, 1);
		inserted->show();
		rightLayout->removeWidget(empty);
		empty->hide();
		hasEmpty = false;
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
	foreach (DragingWidget *widget, findChildren<DragingWidget *>())
		if (!widget->isVisible())
			widget->deleteLater();
	if (hasEmpty)
	{
		empty->hide();
		hasEmpty = false;
		repopulateStuff();
		updateSettings();
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
}

void MainFrameWidget::networkStatusChange(NetworkManager::Status status)
{
	if (status == NetworkManager::DISCONNECTED)
		connexionStatus->setPixmap(QPixmap::fromImage(QImage(":/Pictures/disconnected.png")));
	else if (status == NetworkManager::CONNECTED)
		connexionStatus->setPixmap(QPixmap::fromImage(QImage(":/Pictures/connecting.png")));
	else
		connexionStatus->setPixmap(QPixmap::fromImage(QImage(":/Pictures/connected.png")));
}
