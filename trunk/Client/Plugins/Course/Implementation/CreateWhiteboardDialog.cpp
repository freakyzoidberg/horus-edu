#include <QTreeView>
#include <QSortFilterProxyModel>
#include <QGridLayout>
#include <QPushButton>

#include "CreateWhiteboardDialog.h"
#include "WhiteBoardModel.h"

CreateWhiteboardDialog::CreateWhiteboardDialog(PluginManager *pluginManager)
{
	setWindowTitle(tr("Start a new class"));
	QGridLayout* dlgLayout = new QGridLayout(this);

	QTreeView* treeView = new QTreeView();
	QAbstractItemModel* model = new WhiteBoardModel(pluginManager);
	QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel(this);
	proxyModel->setFilterRegExp(QRegExp("\\b(ROOT|CLASSES|GRADE|SUBJECT|WHITEBOARD)\\b", Qt::CaseSensitive, QRegExp::RegExp));
	proxyModel->setFilterKeyColumn(1);
	proxyModel->setSourceModel(model);
	treeView->setModel(proxyModel);
	treeView->setAnimated(true);
	treeView->setAutoExpandDelay(100);
	treeView->setRootIsDecorated(false);
	treeView->setHeaderHidden(true);
	treeView->expandAll();
	treeView->setSelectionMode(QAbstractItemView::SingleSelection);
	QObject::connect(treeView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(selectionChanged(QModelIndex,QModelIndex)));

	dlgLayout->addWidget(treeView, 0, 0, 1, 2);
	QPushButton *cancel = new QPushButton(tr("Cancel"));
	QPushButton *start = new QPushButton(tr("Start here"));
	QObject::connect(cancel, SIGNAL(pressed()), this, SLOT(cancel()));
	QObject::connect(start, SIGNAL(pressed()), this, SLOT(startHere()));
	dlgLayout->addWidget(cancel, 1, 0);
	dlgLayout->addWidget(start, 1, 1);
}

void	CreateWhiteboardDialog::startHere()
{
	setResult(QDialog::Accepted);
	close();
}

void	CreateWhiteboardDialog::cancel()
{
	setResult(QDialog::Rejected);
	close();
}

void	CreateWhiteboardDialog::selectionChanged(QModelIndex old,QModelIndex current)
{

}
