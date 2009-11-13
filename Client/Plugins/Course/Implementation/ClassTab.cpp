#include "ClassTab.h"
#include "CreateWhiteboardDialog.h"
#include "CourseWidget.h"

ClassTab::ClassTab(PluginManager *pluginManager, UserData* user) : _pluginManager(pluginManager), _user(user)
{
	_layout = new QGridLayout(this);
	_layout->setMargin(0);
	_layout->setSpacing(0);

	_selectWbWidget = new QWidget;
	QGridLayout* sLayout = new QGridLayout(_selectWbWidget);
	_wbList = new QListView;
	if (_user->level() == LEVEL_TEACHER)
	{
		_wbListModel = new WhiteBoardListModel(pluginManager, user);
	}
	else
	{
		_wbListModel = new WhiteBoardListModel(pluginManager, user);
	}
	_wbList->setModel(_wbListModel);
	_wbList->setSelectionMode(QAbstractItemView::SingleSelection);
	QObject::connect(_wbList->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(wbSelectionChanged(QModelIndex,QModelIndex)));
	_info = new QLabel();
	sLayout->addWidget(_wbList, 0, 0, (_user->level() == LEVEL_TEACHER) ? 4 : 2, 1);
	if (_user->level() == LEVEL_TEACHER)
	{
		_joinButton = new QPushButton(tr("Continue this class"));
		_deleteButton = new QPushButton(tr("Delete this class"));
		_createButton = new QPushButton(tr("Start a new class"));
		QObject::connect(_createButton, SIGNAL(pressed()), this, SLOT(createNewWhiteboard()));
                QObject::connect(_deleteButton, SIGNAL(pressed()), this, SLOT(deleteWhiteboard()));
		sLayout->addWidget(_joinButton, 0, 1);
		sLayout->addWidget(_deleteButton, 1, 1);
		sLayout->addWidget(_createButton, 2, 1);
		sLayout->addWidget(_info, 3, 1);
		_deleteButton->setEnabled(false);
	}
	else
	{
		_joinButton = new QPushButton(tr("Join this class"));
		sLayout->addWidget(_joinButton, 0, 1);
		sLayout->addWidget(_info, 1, 1);
	}
        QObject::connect(_joinButton, SIGNAL(pressed()), this, SLOT(joinWhiteboard()));
	_joinButton->setEnabled(false);
        sLayout->setMargin(2);
        sLayout->setSpacing(2);
	sLayout->setColumnStretch(0, 2);
	sLayout->setColumnStretch(1, 1);

	_layout->addWidget(_selectWbWidget, 0, 0);
}

void	ClassTab::wbSelectionChanged(QModelIndex current, QModelIndex previous)
{
	if (current.isValid())
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
        wbdata->setStatus(Data::DELETING);
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
