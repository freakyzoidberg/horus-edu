#ifndef CREATEWHITEBOARDDIALOG_H
#define CREATEWHITEBOARDDIALOG_H

#include <QDialog>
#include <QModelIndex>

#include "../../../../Common/PluginManager.h"

class CreateWhiteboardDialog : public QDialog
{
	Q_OBJECT

public:
	CreateWhiteboardDialog(PluginManager *pluginManager);

public slots:
	void	selectionChanged(QModelIndex,QModelIndex);
	void	startHere();
	void	cancel();
};

#endif // CREATEWHITEBOARDDIALOG_H
