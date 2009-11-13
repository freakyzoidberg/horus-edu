#ifndef CREATEWHITEBOARDDIALOG_H
#define CREATEWHITEBOARDDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include <QSortFilterProxyModel>
#include <QAbstractItemModel>
#include <QPushButton>

#include "../../../../Common/PluginManager.h"
#include "../../../../Common/TreeData.h"

class CreateWhiteboardDialog : public QDialog
{
	Q_OBJECT

public:
	CreateWhiteboardDialog(PluginManager *pluginManager);
        TreeData*   getNode() { return _node; }

public slots:
	void	selectionChanged(QModelIndex,QModelIndex);
	void	startHere();
	void	cancel();

private:
        TreeData*   _node;
        QAbstractItemModel* _model;
        QSortFilterProxyModel* _proxyModel;
        QPushButton *_cancel;
        QPushButton *_start;
};

#endif // CREATEWHITEBOARDDIALOG_H
