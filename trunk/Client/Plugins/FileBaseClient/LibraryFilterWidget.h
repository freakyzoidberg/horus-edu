#ifndef LIBRARYFILTERWIDGET_H
#define LIBRARYFILTERWIDGET_H

#include <QWidget>
#include <QComboBox>
class Data;
class PluginManager;
class TreeDataPlugin;
class UserDataPlugin;

class LibraryFilterWidget : public QWidget
{
Q_OBJECT
public:
	LibraryFilterWidget(PluginManager* pluginManager, QWidget *parent = 0);

private slots:
	void updateFilters(Data* = 0);

public:
	QComboBox		grades;
	QComboBox		subjects;
	QComboBox		owners;
private:
	TreeDataPlugin*	_treeDataPlugin;
	UserDataPlugin*	_userDataPlugin;
};

#endif // LIBRARYFILTERWIDGET_H
