#ifndef LIBRARYMODEL_H
#define LIBRARYMODEL_H

#include <QAbstractListModel>
class FileDataPlugin;
class PluginManager;

class LibraryModel : public QAbstractListModel
{
public:
	LibraryModel(PluginManager* pluginManager);

private:
	int				rowCount(const QModelIndex& index) const;
	QModelIndex		index(int row, int col, const QModelIndex& parent) const;
	QVariant		data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	
	FileDataPlugin*	_plugin;
};

#endif // LIBRARYMODEL_H
