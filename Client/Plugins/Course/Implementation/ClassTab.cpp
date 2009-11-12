#include "ClassTab.h"
#include "CreateWhiteboardDialog.h"

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
	_joinButton->setEnabled(false);
	sLayout->setColumnStretch(0, 2);
	sLayout->setColumnStretch(1, 1);

	_layout->addWidget(_selectWbWidget, 0, 0);
}

void	ClassTab::wbSelectionChanged(QModelIndex old, QModelIndex current)
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
}
