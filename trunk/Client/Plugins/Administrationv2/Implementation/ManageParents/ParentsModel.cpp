#include	"ParentsModel.h"

ParentsModel::ParentsModel(const QHash<quint32, UserData*>&  _users, QObject *parent) : QAbstractListModel(parent), users(_users)
{
}

QVariant	ParentsModel::data(const QModelIndex &index, int role) const
{
	int		i;

	if (!index.isValid() || index.row() >= users.size())
		return (QVariant());
	i = 0;
	foreach (UserData* user, users)
	{
		if (index.row() == i && user->level() == LEVEL_FAMILY)
		{
			if (role == Qt::DisplayRole || role == Qt::EditRole)
				return (user->login());
			else if (role == Qt::UserRole)
				return (user->id());
		}
		i++;
	}
	return (QVariant());
}

int         ParentsModel::rowCount(const QModelIndex &parent) const
{
	quint32	i;
	
	i = 0;
	foreach (UserData* user, users)
		if (user->level() == LEVEL_FAMILY)
			i++;
	return (i);
}
