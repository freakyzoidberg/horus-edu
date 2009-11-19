#include	"AdministrativesModel.h"

#include	<QIcon>
#include	<QDebug>

AdministrativesModel::AdministrativesModel(const QHash<quint32, UserData*>&  _users, QObject *Administrative) : QAbstractListModel(Administrative), users(_users)
{
}

QVariant	AdministrativesModel::data(const QModelIndex &index, int role) const
{
	int		i = 0;
	qDebug() << "Asked: " << index.row() << " / " << index.column();
	foreach (UserData* user, users)
	{
		qDebug() << user;
		if (user->level() == LEVEL_ADMINISTRATOR)
			qDebug() << "et un adm" << i;
		if (user->level() != LEVEL_ADMINISTRATOR || user->status() == Data::DELETED || user->status() == Data::EMPTY)
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
	qDebug() << "not fouund";
	return (QVariant());
}

int			AdministrativesModel::rowCount(const QModelIndex &) const
{
	quint32	i = 0;
	foreach (UserData* user, users)
		if (user->level() == LEVEL_ADMINISTRATOR && user->status() != Data::DELETED && user->status() != Data::EMPTY)
			i++;
	qDebug() << i;
	return (i);
}
