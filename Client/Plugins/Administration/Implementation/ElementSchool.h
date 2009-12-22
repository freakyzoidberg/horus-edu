#ifndef						__ELEMENTSCHOOL_H__
# define					__ELEMENTSCHOOL_H__

# include					"StructureElement.h"

# include					<QLabel>
# include					<QSortFilterProxyModel>

# include					"../../../../Common/UserDataPlugin.h"

class						ElementSchool : public StructureElement
{
	Q_OBJECT

public:
	ElementSchool(QWidget *parent, TreeDataPlugin *treeDataPlugin, UserDataPlugin *userDataPlugin);
	void					update();

protected:
	void					addElement();
	void					editElement();
	void					removeElement();
	void					validateElement();

private:
	QLabel					*name;
	QLabel					*studentsNumber;
	QLabel					*parentsNumber;
	QLabel					*teachersNumber;
	QLabel					*administrativesNumber;
	QLabel					*classesNumber;
	QLabel					*usersNumber;
	QSortFilterProxyModel	*studentsModel;
	QSortFilterProxyModel	*parentsModel;
	QSortFilterProxyModel	*teachersModel;
	QSortFilterProxyModel	*administrativesModel;
	QSortFilterProxyModel	*classesModel;
	QAbstractItemModel		*usersModel;

public slots:
	void					treeUpdated();
	void					userUpdated();
};

#endif //	__ELEMENTSCHOOL_H__
