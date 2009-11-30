#ifndef LIBRARYFILTER_H
#define LIBRARYFILTER_H

#include <QSortFilterProxyModel>
class TreeData;

class LibraryFilter : public QSortFilterProxyModel
{
	Q_OBJECT
public:
	LibraryFilter(QAbstractListModel* model, QObject* parent = 0);

public slots:
	void				treeSelectionChange(const QItemSelection& selected, const QItemSelection& deselected);

private:
	bool				filterAcceptsRow(int source_row, const QModelIndex& source_parent) const;
	QList<TreeData*>	_nodes;
};

#endif // LIBRARYFILTER_H
