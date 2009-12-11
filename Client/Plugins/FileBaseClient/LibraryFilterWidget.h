#ifndef LIBRARYFILTERWIDGET_H
#define LIBRARYFILTERWIDGET_H

#include <QWidget>
#include <QComboBox>
class Data;
class PluginManager;
class TreeDataPlugin;
class UserDataPlugin;
class LibraryFilterProxyModel;

class LibraryFilterWidget : public QWidget
{
Q_OBJECT
public:
	LibraryFilterWidget(PluginManager* pluginManager, LibraryFilterProxyModel* filter, QWidget *parent = 0);

private slots:
	void			comboBoxChanged(int);

public:
	QComboBox		grades;
	QComboBox		subjects;
	QComboBox		owners;
private:
	TreeDataPlugin*	_treeDataPlugin;
	UserDataPlugin*	_userDataPlugin;
	LibraryFilterProxyModel*	_filter;
};

#endif // LIBRARYFILTERWIDGET_H
