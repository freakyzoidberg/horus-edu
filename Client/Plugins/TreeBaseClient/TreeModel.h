#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
class Data;
class TreeData;
class TreeDataPlugin;

class TreeModel : public QAbstractItemModel
{
	Q_OBJECT
public:
	TreeModel(const TreeDataPlugin* plugin);
	int							rowCount(const QModelIndex &parent = QModelIndex()) const;
	int							columnCount(const QModelIndex &parent = QModelIndex()) const;
	QModelIndex					parent(const QModelIndex &child) const;
	QModelIndex					index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
	QVariant					data(const QModelIndex &index, int role = Qt::DisplayRole) const;
private slots:
	void						dataStatusChanged(Data* data);
private:
	void						inserData(TreeData* parent, Data* data);
	void						removeData(TreeData* parent, Data* data);
	const TreeDataPlugin*		_plugin;
	QMultiHash<TreeData*,Data*>	_data;
};

#endif // TREEMODEL_H
