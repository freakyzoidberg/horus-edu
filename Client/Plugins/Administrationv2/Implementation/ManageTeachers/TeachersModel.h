#ifndef								__TEACHERSMODEL_H__
# define							__TEACHERSMODEL_H__

# include							<QAbstractItemModel>

# include							"../../../../../Common/UserData.h"

class								TeachersModel: public QAbstractListModel
{
	Q_OBJECT

public:
	TeachersModel(const QHash<quint32, UserData*>& users, QObject *Teacher = 0);
	QVariant						data(const QModelIndex &index, int role) const;
	int								rowCount(const QModelIndex &Teacher = QModelIndex()) const;


private:
	const QHash<quint32,UserData*>&	users;
	quint32							level;
};

#endif //							__TeacherSMODEL_H__
