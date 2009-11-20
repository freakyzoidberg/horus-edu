#ifndef USERDATAMODEL_H
#define USERDATAMODEL_H

#include "../../../Common/DataImplementations/UserDataBase/UserDataBase.h"

class UserDataModel : public QAbstractListModel
{
	Q_OBJECT
public:
	UserDataModel(UserDataBasePlugin* plugin);
	QModelIndex			index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
//	QModelIndex			parent(const QModelIndex &child) const;
	int					rowCount(const QModelIndex &parent = QModelIndex()) const;
	inline int			columnCount(const QModelIndex &) const { return 3; }
	QVariant			data(const QModelIndex &index, int role = Qt::DisplayRole) const;
//	inline bool			hasChildren ( const QModelIndex &) const { return false; }
private slots:
	void				dataStatusChanged(Data*);
private:
	UserDataBasePlugin*	_plugin;
};

#endif // USERDATAMODEL_H
