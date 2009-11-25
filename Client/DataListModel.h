#ifndef DATALISTMODEL_H
#define DATALISTMODEL_H

#include <QAbstractListModel>
class Data;
class DataPlugin;

class DataListModel : public QAbstractListModel
{
	Q_OBJECT
public:
	DataListModel(const DataPlugin* plugin);
	int					rowCount(const QModelIndex &parent = QModelIndex()) const;
	QModelIndex			index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
	QVariant			data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	Qt::DropActions		supportedDropActions() const;
	QMimeData*			mimeData(const QModelIndexList &indexes) const;
	Qt::ItemFlags		flags(const QModelIndex &index) const;
	bool				dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);

private slots:
	void				dataStatusChanged(Data*);
protected:
	const DataPlugin*	_plugin;
	QList<Data*>		_list;
};

#endif // DATALISTMODEL_H
