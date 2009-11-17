#include	"AdministrativesModel.h"

#include	<QIcon>

AdministrativesModel::AdministrativesModel(const QHash<quint32, UserData*>&  _users, QObject *Administrative) : QAbstractListModel(Administrative), users(_users)
{
}

QVariant	AdministrativesModel::data(const QModelIndex &index, int role) const
{
	int		i = 0;
	foreach (UserData* user, users)
	{
		if (user->level() != LEVEL_ADMINISTRATOR)
			continue;

		if (index.row() == i)
		{
			if (role == Qt::DisplayRole || role == Qt::EditRole)
				return (user->name() +  " " + user->surname());
			else if (role == Qt::UserRole)
				return (user->id());
			else if (role == Qt::DecorationRole)
				return (QIcon(":/Icons/administrator.png"));
			return (QVariant());
		}
		i++;
	}
	return (QVariant());
}

int			AdministrativesModel::rowCount(const QModelIndex &) const
{
	quint32	i = 0;
	foreach (UserData* user, users)
		if (user->level() == LEVEL_FAMILY)
			i++;
	return (i);
}
