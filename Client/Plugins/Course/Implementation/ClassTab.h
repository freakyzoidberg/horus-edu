#ifndef CLASSTAB_H
#define CLASSTAB_H

#include <QWidget>
#include <QGridLayout>
#include <QListView>
#include <QPushButton>
#include <QLabel>

#include "../../../../Common/PluginManager.h"
#include "../../../../Common/UserData.h"
#include "WhiteBoardListModel.h"

class ClassTab : public QWidget
{
	Q_OBJECT

public:
	ClassTab(PluginManager *pluginManager, UserData* user);

public slots:
	void			wbSelectionChanged(QModelIndex old, QModelIndex current);
	void			createNewWhiteboard();

private:
	PluginManager*	_pluginManager;
	UserData*		_user;
	QGridLayout*	_layout;
	QWidget*		_selectWbWidget;
	QListView*		_wbList;
	QPushButton*	_joinButton;
	QPushButton*	_createButton;
	QPushButton*	_deleteButton;
	QLabel*			_info;
	QWidget*		_createWbWidget;

	WhiteBoardListModel*	_wbListModel;
};

#endif // CLASSTAB_H
