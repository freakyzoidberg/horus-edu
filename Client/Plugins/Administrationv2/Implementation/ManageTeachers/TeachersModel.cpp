#include	"TeachersModel.h"

#include	<QIcon>

TeachersModel::TeachersModel(const QHash<quint32, UserData*>&  _users, QObject *Teacher) : QAbstractListModel(Teacher), users(_users)
{
}

QVariant	TeachersModel::data(const QModelIndex &index, int role) const
{
	int		i = 0;
	foreach (UserData* user, users)
	{
		if (user->level() != LEVEL_TEACHER || user->status() == Data::DELETED || user->status() == Data::EMPTY)
			continue;

		if (index.row() == i)
		{
			if (role == Qt::DisplayRole || role == Qt::EditRole)
				return (user->name() +  " " + user->surname());
			else if (role == Qt::UserRole)
				return (user->id());
			else if (role == Qt::DecorationRole)
				return (QIcon(":/Icons/teachers.png"));
			return (QVariant());
		}
		i++;
	}
	return (QVariant());
}

int			TeachersModel::rowCount(const QModelIndex &) const
{
	quint32	i = 0;
	foreach (UserData* user, users)
		if (user->level() == LEVEL_FAMILY && user->status() != Data::DELETED && user->status() != Data::EMPTY)
			i++;
	return (i);
}
