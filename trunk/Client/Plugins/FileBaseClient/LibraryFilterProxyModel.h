#ifndef LibraryFilterProxyModel_H
#define LibraryFilterProxyModel_H

#include <QSortFilterProxyModel>
class Data;

class LibraryFilterProxyModel : public QSortFilterProxyModel
{
	Q_OBJECT
public:
	LibraryFilterProxyModel(QAbstractListModel* model, QObject* parent = 0);
	void				nodeListChanged(const QList<Data*>& list);

private:
	bool				filterAcceptsRow(int source_row, const QModelIndex& source_parent) const;
	QList<Data*>		_nodes;
};

#endif // LibraryFilterProxyModel_H
