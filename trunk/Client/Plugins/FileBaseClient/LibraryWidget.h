#ifndef LIBRARYWIDGET_H
#define LIBRARYWIDGET_H

#include <QWidget>
#include <QItemSelectionModel>
#include <QFormLayout>
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
	QFormLayout*			_detailLayout;
private slots:
	void					treeSelectionChange(const QItemSelection& selected, const QItemSelection& deselected);
	void					fileSelectionChange(const QItemSelection& selected, const QItemSelection& deselected);
};

#endif // LIBRARYWIDGET_H
