#ifndef LIBRARYWIDGET_H
#define LIBRARYWIDGET_H

#include <QWidget>
#include <QItemSelectionModel>
class QSortFilterProxyModel;
class PluginManager;

class LibraryWidget : public QWidget
{
	Q_OBJECT

public:
	LibraryWidget(PluginManager* pluginManager);
private:
	QItemSelectionModel*	_treeSelection;
	QSortFilterProxyModel*	_filter;
private slots:
	void					treeSelectionChange(const QItemSelection& selected, const QItemSelection& deselected);
};

#endif // LIBRARYWIDGET_H
