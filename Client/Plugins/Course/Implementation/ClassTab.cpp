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
#include "ClassTab.h"
#include "CreateWhiteboardDialog.h"
#include "CourseWidget.h"
#include "../../../../Common/DataImplementations/WhiteBoardData/WhiteBoardDataPlugin.h"

ClassTab::ClassTab(PluginManager *pluginManager, UserData* user) : _pluginManager(pluginManager), _user(user)
{
	_layout = new QGridLayout(this);
	_layout->setMargin(0);
	_layout->setSpacing(0);

	_selectWbWidget = new QWidget;
	QGridLayout* sLayout = new QGridLayout(_selectWbWidget);
	_wbList = new QListView;
    QObject::connect(pluginManager->findPlugin<WhiteBoardDataPlugin*>(), SIGNAL(dataCreated(Data*)), this, SLOT(updateWbList(Data*)));
    QObject::connect(pluginManager->findPlugin<WhiteBoardDataPlugin*>(), SIGNAL(dataRemoved(Data*)), this, SLOT(updateWbList(Data*)));
	_wbListModel = new WhiteBoardListModel(pluginManager, user);
	_wbList->setModel(_wbListModel);
	//_wbList->setModel(pluginManager->findPlugin<WhiteBoardDataPlugin*>()->listModel());
	_wbList->setSelectionMode(QAbstractItemView::SingleSelection);
	QObject::connect(_wbList->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(wbSelectionChanged(QItemSelection,QItemSelection)));
	_info = new QLabel();
	sLayout->addWidget(_wbList, 0, 0, (_user->level() == LEVEL_TEACHER) ? 5 : 3, 1);
	QLabel *actionTitle = new QLabel(tr("Actions:"));
	actionTitle->setProperty("isTitle", true);
	actionTitle->setProperty("isRound", true);
	sLayout->addWidget(actionTitle, 0, 1);
	if (_user->level() == LEVEL_TEACHER)
	{
		_joinButton = new QPushButton(QIcon(":/Ui/desk-join.png"), tr("Continue this class"));
		_deleteButton = new QPushButton(QIcon(":/Ui/desk-del.png"), tr("Delete this class"));
		_createButton = new QPushButton(QIcon(":/Ui/desk-add.png"), tr("Start a new class"));
		QObject::connect(_createButton, SIGNAL(pressed()), this, SLOT(createNewWhiteboard()));
        QObject::connect(_deleteButton, SIGNAL(pressed()), this, SLOT(deleteWhiteboard()));
		sLayout->addWidget(_joinButton, 1, 1);
		sLayout->addWidget(_deleteButton, 2, 1);
		sLayout->addWidget(_createButton, 3, 1);
		sLayout->addWidget(_info, 4, 1);
		_deleteButton->setEnabled(false);
	}
	else
	{
		_joinButton = new QPushButton(QIcon(":/Ui/desk-join.png"), tr("Join this class"));
		sLayout->addWidget(_joinButton, 1, 1);
		sLayout->addWidget(_info, 2, 1);
	}
    QObject::connect(_joinButton, SIGNAL(pressed()), this, SLOT(joinWhiteboard()));
	_joinButton->setEnabled(false);
	_joinButton->setMinimumWidth(200);
    sLayout->setMargin(2);
    sLayout->setSpacing(2);
	sLayout->setRowStretch((_user->level() == LEVEL_TEACHER) ? 4 : 2, 100);

	_layout->addWidget(_selectWbWidget, 0, 0);
}

void	ClassTab::wbSelectionChanged(QItemSelection current, QItemSelection previous)
{
	if (_wbList->selectionModel()->hasSelection())
	{
		_joinButton->setEnabled(true);
		if (_user->level() == LEVEL_TEACHER)
			_deleteButton->setEnabled(true);
	}
	else
	{
		_joinButton->setEnabled(false);
		if (_user->level() == LEVEL_TEACHER)
			_deleteButton->setEnabled(false);
	}
}

void	ClassTab::createNewWhiteboard()
{
	CreateWhiteboardDialog dialog(_pluginManager);
	dialog.exec();
        if (dialog.result() == QDialog::Accepted)
        {
            WhiteBoardData* wbd = _pluginManager->findPlugin<WhiteBoardDataPlugin *>()->whiteBoard(dialog.getNode());
            wbd->setSyncMode(WhiteBoardData::FULL_SYNC);
            wbd->save();
            doJoinWhiteboard(wbd);
        }
}

void    ClassTab::doJoinWhiteboard(WhiteBoardData *wbd)
{
    _layout->removeWidget(_selectWbWidget);
    _selectWbWidget->hide();
    _wbWidget = new QWidget;
    QGridLayout* wbLayout = new QGridLayout(_wbWidget);
    wbLayout->setMargin(0);
    wbLayout->setSpacing(0);
    CourseWidget* widget = new CourseWidget(this, wbd, _pluginManager, _user);
    QPushButton* back = new QPushButton(tr("Leave this class"));
    wbLayout->addWidget(widget);
    wbLayout->addWidget(back);
    widget->show();
    back->show();
    connect(back, SIGNAL(clicked()), this, SLOT(leaveWhiteboard()));
    _layout->addWidget(_wbWidget, 0, 0);
}

void    ClassTab::leaveWhiteboard()
{
    _layout->removeWidget(_wbWidget);
    delete _wbWidget;
    _layout->addWidget(_selectWbWidget, 0, 0);
    _selectWbWidget->show();
}

void    ClassTab::deleteWhiteboard()
{
    WhiteBoardData* wbdata = _wbListModel->getWhiteboard(_wbList->currentIndex());
    if (wbdata)
    {
		wbdata->remove();
    }
}

void    ClassTab::joinWhiteboard()
{
    WhiteBoardData* wbdata = _wbListModel->getWhiteboard(_wbList->currentIndex());
    if (wbdata)
    {
        doJoinWhiteboard(wbdata);
    }
}

void    ClassTab::updateWbList(Data*)
{
    _wbList->reset();
}
