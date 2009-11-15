#ifndef								__PARENTSMODEL_H__
# define							__PARENTSMODEL_H__

# include							<QAbstractItemModel>

# include							"../../../../Common/UserData.h"

class								ParentsModel: public QAbstractListModel
{
	Q_OBJECT

public:
	ParentsModel(const QHash<quint32, UserData*>& users, QObject *parent = 0);
	QVariant						data(const QModelIndex &index, int role) const;
	int								rowCount(const QModelIndex &parent = QModelIndex()) const;


private:
	const QHash<quint32,UserData*>&	users;
	quint32							level;
};

#endif //							__PARENTSMODEL_H__
