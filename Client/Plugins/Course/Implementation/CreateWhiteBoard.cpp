#include	"CreateWhiteBoard.h"

#include	<QSortFilterProxyModel>
#include	<QItemSelectionModel>
#include	<QVBoxLayout>

#include	"../../../../Common/DataImplementations/WhiteBoardData/WhiteBoardData.h"
#include	"../../../../Common/TreeData.h"

#include	"WhiteBoardModel.h"

CreateWhiteBoard::CreateWhiteBoard(QWidget *parent, PluginManager *pluginManager) : QWidget(parent), _pluginManager(pluginManager)
{
	this->ui.setupUi(this);
	QAbstractItemModel		*model = new WhiteBoardModel(pluginManager);
    QSortFilterProxyModel	*proxyModel = new QSortFilterProxyModel(this);
	proxyModel->setFilterRegExp(QRegExp("\\b(ROOT|CLASSES|GRADE|SUBJECT|WHITEBOARD)\\b", Qt::CaseSensitive, QRegExp::RegExp));
	proxyModel->setFilterKeyColumn(1);
	proxyModel->setSourceModel(model);
	this->ui.treeView->setModel(proxyModel);
	this->ui.treeView->expandAll();
	this->ui.treeView->setAnimated(true);
    this->ui.treeView->setAutoExpandDelay(500);
	this->ui.treeView->setRootIsDecorated(false);
    this->ui.treeView->setHeaderHidden(true);
	connect(this->ui.button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
	this->ui.syncInput->insertItem(0, tr("No Sync"), WhiteBoardData::NO_SYNC);
	this->ui.syncInput->insertItem(0, tr("Semi Sync"), WhiteBoardData::SEMI_SYNC);
	this->ui.syncInput->insertItem(0, tr("Full Sync"), WhiteBoardData::FULL_SYNC);
}

void		CreateWhiteBoard::buttonClicked()
{
	if (this->ui.nameInput->isModified())
	{
		if (this->ui.syncInput->currentIndex() >= 0)
		{
			QItemSelectionModel *selection = this->ui.treeView->selectionModel();
			if (selection->hasSelection())
			{
				QModelIndexList	selected = selection->selectedIndexes();
				if (selected.count() == 1)
				{
					Data* data = (Data *)(qobject_cast<QSortFilterProxyModel *>(this->ui.treeView->model())->mapToSource(selected.at(0)).internalPointer());
					TreeData *treeData = qobject_cast<TreeData *>(data);
					WhiteBoardData *wbd = _pluginManager->findPlugin<WhiteBoardDataPlugin *>()->getWhiteBoard(treeData);
					wbd->setSyncMode((WhiteBoardData::SyncMode)(this->ui.syncInput->itemData(this->ui.syncInput->currentIndex(), Qt::UserRole).toUInt()));
					wbd->save();
					emit whiteBoardCreated(wbd);
				}
				else
					qWarning() << tr("Please select only one place to create the whiteboard");
			}
			else
				qWarning() << tr("Please select a place to create the whiteboard");
		}
		else
			qWarning() << tr("Please use a sync mode");
	}
	else
		qWarning() << tr("Please fill a name");
}
