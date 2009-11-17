#include	"ParentsModel.h"

ParentsModel::ParentsModel(const QHash<quint32, UserData*>&  _users, QObject *parent) : QAbstractListModel(parent), users(_users)
{
}

QVariant	ParentsModel::data(const QModelIndex &index, int role) const
{
	int		i = 0;
	foreach (UserData* user, users)
	{
		if (user->level() != LEVEL_FAMILY)
			continue;

		if (index.row() == i)
		{
			if (role == Qt::DisplayRole || role == Qt::EditRole)
				return (user->name() +  user->surname());
			else if (role == Qt::UserRole)
				return (user->id());
		}
		i++;
	}
	return (QVariant());
}

int			ParentsModel::rowCount(const QModelIndex &) const
{
	quint32	i = 0;
	foreach (UserData* user, users)
		if (user->level() == LEVEL_FAMILY)
			i++;
	return (i);
}
