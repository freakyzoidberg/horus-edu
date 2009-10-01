#include	"JoinWhiteBoard.h"
#include		<QMenu>
#include	<QSortFilterProxyModel>
#include	<QVBoxLayout>

#include	"WhiteBoardModel.h"

JoinWhiteBoard::JoinWhiteBoard(QWidget *parent, PluginManager *pluginManager) : QWidget(parent), _pluginManager(pluginManager)
{
	this->ui.setupUi(this);
	QAbstractItemModel		*model = new WhiteBoardModel(pluginManager);
    QSortFilterProxyModel	*proxyModel = new QSortFilterProxyModel(this);
	proxyModel->setFilterRegExp(QRegExp("\\b(ROOT|CLASSES|GRADE|SUBJECT|WHITEBOARD)\\b", Qt::CaseSensitive, QRegExp::RegExp));
	proxyModel->setFilterKeyColumn(1);
	proxyModel->setSourceModel(model);
	this->ui.treeView->setModel(proxyModel);
	this->ui.treeView->setContextMenuPolicy(Qt::CustomContextMenu);
	this->ui.treeView->expandAll();
	this->ui.treeView->setAnimated(true);
    this->ui.treeView->setAutoExpandDelay(500);
	this->ui.treeView->setRootIsDecorated(false);
    this->ui.treeView->setHeaderHidden(true);
	connect(this->ui.button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
	connect(pluginManager->findPlugin<WhiteBoardDataPlugin *>(), SIGNAL(dataUpdated(Data *)), this, SLOT(updateTree()));
	connect(this->ui.treeView, SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(ShowContextMenu(const QPoint&)));

}

void		JoinWhiteBoard::updateTree()
{
	this->ui.treeView->reset();
	this->ui.treeView->expandAll();
}


void		JoinWhiteBoard::ShowContextMenu(const QPoint &pnt)
{
	QList<QAction *> actions;
	if (this->ui.treeView->indexAt(pnt).isValid())
	{
		QAction *joinBrd = new QAction(QIcon(":/Ui/edit.png"), tr("&Join Board..."), this);
		joinBrd->setShortcuts(QKeySequence::Open);
		joinBrd->setStatusTip(tr("Add a new group"));
		connect(joinBrd, SIGNAL(triggered(QAction *)), this, SLOT(joinBoard(QAction *)));
	}
	if (actions.count() > 0)
		QMenu::exec(actions, this->ui.treeView->mapToGlobal(pnt));

}

void		JoinWhiteBoard::joinBoard()
{
	QItemSelectionModel *selection = this->ui.treeView->selectionModel();
	if (selection->hasSelection())
	{
		QModelIndexList	selected = selection->selectedIndexes();
		if (selected.count() == 1)
		{
			Data* data = (Data *)(qobject_cast<QSortFilterProxyModel *>(this->ui.treeView->model())->mapToSource(selected.at(0)).internalPointer());
			WhiteBoardData *wbd = qobject_cast<WhiteBoardData *>(data);
			if (wbd)
				emit whiteBoardJoined(wbd);
			else
				qWarning() << tr("Please select one whiteboard");
		}
		else
			qWarning() << tr("Please select one whiteboard");
	}
	else
		qWarning() << tr("Please select a place to create the whiteboard");
}

void		JoinWhiteBoard::buttonClicked()
{
	QItemSelectionModel *selection = this->ui.treeView->selectionModel();
	if (selection->hasSelection())
	{
		QModelIndexList	selected = selection->selectedIndexes();
		if (selected.count() == 1)
		{
			Data* data = (Data *)(qobject_cast<QSortFilterProxyModel *>(this->ui.treeView->model())->mapToSource(selected.at(0)).internalPointer());
			WhiteBoardData *wbd = qobject_cast<WhiteBoardData *>(data);
			if (wbd)
				emit whiteBoardJoined(wbd);
			else
				qWarning() << tr("Please select one whiteboard");
		}
		else
			qWarning() << tr("Please select one whiteboard");
	}
	else
		qWarning() << tr("Please select a place to create the whiteboard");	
}
