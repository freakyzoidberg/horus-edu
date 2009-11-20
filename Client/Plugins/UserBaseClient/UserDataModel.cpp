#include "UserDataModel.h"

UserDataModel::UserDataModel(UserDataBasePlugin* plugin)
{
	_plugin = plugin;
}

QModelIndex UserDataModel::index(int row, int column, const QModelIndex &) const
{
	int rows = 0;
	foreach (UserData* u, _plugin->allUser())
		if (u->status() != Data::EMPTY && u->status() != Data::DELETED && u->status() != Data::DELETING)
		{
			if (row == rows)
				return createIndex(row, column, u);
			rows++;
		}
	return QModelIndex();
}

//QModelIndex UserDataModel::parent(const QModelIndex &) const
//{
//	return QModelIndex();
//}

int UserDataModel::rowCount(const QModelIndex &) const
{
	int rows = 0;
	foreach (UserData* u, _plugin->allUser())
		if (u->status() != Data::EMPTY && u->status() != Data::DELETED && u->status() != Data::DELETING)
			rows++;
	return rows;
}

QVariant UserDataModel::data(const QModelIndex &index, int role) const
{
	return ((UserDataBase*)(index.internalPointer()))->data(index.column(), role);
}

void UserDataModel::dataStatusChanged(Data*)
{
	reset();
}
