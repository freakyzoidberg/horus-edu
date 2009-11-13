#include <QTreeView>
#include <QGridLayout>

#include "CreateWhiteboardDialog.h"
#include "WhiteBoardModel.h"

CreateWhiteboardDialog::CreateWhiteboardDialog(PluginManager *pluginManager) : _node(NULL)
{
	setWindowTitle(tr("Start a new class"));
	QGridLayout* dlgLayout = new QGridLayout(this);

	QTreeView* treeView = new QTreeView();
        _model = new WhiteBoardModel(pluginManager);
        _proxyModel = new QSortFilterProxyModel(this);
        _proxyModel->setFilterRegExp(QRegExp("\\b(ROOT|CLASSES|GRADE|SUBJECT|WHITEBOARD)\\b", Qt::CaseSensitive, QRegExp::RegExp));
        _proxyModel->setFilterKeyColumn(1);
        _proxyModel->setSourceModel(_model);
        treeView->setModel(_proxyModel);
	treeView->setAnimated(true);
	treeView->setAutoExpandDelay(100);
	treeView->setRootIsDecorated(false);
	treeView->setHeaderHidden(true);
	treeView->expandAll();
	treeView->setSelectionMode(QAbstractItemView::SingleSelection);
	QObject::connect(treeView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(selectionChanged(QModelIndex,QModelIndex)));

	dlgLayout->addWidget(treeView, 0, 0, 1, 2);
        _cancel = new QPushButton(tr("Cancel"));
        _start = new QPushButton(tr("Start here"));
        _start->setEnabled(false);
        QObject::connect(_cancel, SIGNAL(pressed()), this, SLOT(cancel()));
        QObject::connect(_start, SIGNAL(pressed()), this, SLOT(startHere()));
        dlgLayout->addWidget(_cancel, 1, 0);
        dlgLayout->addWidget(_start, 1, 1);
}

void	CreateWhiteboardDialog::startHere()
{
        if (_node)
            done(QDialog::Accepted);
        else
            done(QDialog::Rejected);
}

void	CreateWhiteboardDialog::cancel()
{
        done(QDialog::Rejected);
}

void	CreateWhiteboardDialog::selectionChanged(QModelIndex current, QModelIndex previous)
{
    _node = NULL;
    _start->setEnabled(false);
    if (current.isValid() && current.internalPointer() != NULL)
    {
        TreeData *tdata = qobject_cast<TreeData*>(static_cast<QObject*>(_proxyModel->mapToSource(current).internalPointer()));
        if (tdata && tdata->type() == "SUBJECT")
        {
            _node = tdata;
            _start->setEnabled(true);
        }
    }
}
