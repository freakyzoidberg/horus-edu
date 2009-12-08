#ifndef LibraryFilterProxyModel_H
#define LibraryFilterProxyModel_H

#include <QSortFilterProxyModel>
class TreeData;

class LibraryFilterProxyModel : public QSortFilterProxyModel
{
	Q_OBJECT
public:
	LibraryFilterProxyModel(QAbstractListModel* model, QObject* parent = 0);

public slots:
	void				treeSelectionChange(const QItemSelection& selected, const QItemSelection& deselected);

private:
	bool				filterAcceptsRow(int source_row, const QModelIndex& source_parent) const;
	QList<TreeData*>	_nodes;
};

#endif // LibraryFilterProxyModel_H
