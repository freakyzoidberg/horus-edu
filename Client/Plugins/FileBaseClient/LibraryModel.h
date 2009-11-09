#ifndef LIBRARYMODEL_H
#define LIBRARYMODEL_H


#include <QAbstractListModel>

class FileDataPlugin;
class LibraryModel : public QAbstractListModel
{
public:
	LibraryModel(FileDataPlugin* plugin) { _plugin = plugin; }

private:
	int				rowCount(const QModelIndex& index) const;
	QModelIndex		index(int row, int col, const QModelIndex& parent) const;
	QVariant		data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	
	FileDataPlugin*	_plugin;
};


class TreeDataPlugin;
class TreeModel : public QAbstractItemModel
{
public:
	TreeModel(TreeDataPlugin* plugin) { _plugin = plugin; }

private:
	int				rowCount(const QModelIndex& index) const;
	int				columnCount(const QModelIndex &parent = QModelIndex()) const;
	QModelIndex		parent(const QModelIndex &child) const;
	QModelIndex		index(int row, int col, const QModelIndex& parent) const;
	QVariant		data(const QModelIndex& index, int role = Qt::DisplayRole) const;

	TreeDataPlugin*	_plugin;
};

#endif // LIBRARYMODEL_H
