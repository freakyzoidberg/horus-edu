#ifndef								__AdministrativeSMODEL_H__
# define							__AdministrativeSMODEL_H__

# include							<QAbstractItemModel>

# include							"../../../../../Common/UserData.h"

class								AdministrativesModel: public QAbstractListModel
{
	Q_OBJECT

public:
	AdministrativesModel(const QHash<quint32, UserData*>& users, QObject *Administrative = 0);
	QVariant						data(const QModelIndex &index, int role) const;
	int								rowCount(const QModelIndex &Administrative = QModelIndex()) const;


private:
	const QHash<quint32,UserData*>&	users;
	quint32							level;
};

#endif //							__AdministrativeSMODEL_H__
