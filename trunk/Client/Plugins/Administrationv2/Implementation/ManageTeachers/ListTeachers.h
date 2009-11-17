#ifndef				__LISTTEACHERS_H__
# define			__LISTTEACHERS_H__

# include			<QWidget>

# include			<QListView>
# include			<QPushButton>
# include			<QBoxLayout>

# include			"../../../../../Common/PluginManager.h"
# include			"../../../../../Common/UserData.h"
# include			"DisplayTeacher.h"

class				ListTeachers : public QWidget
{
	Q_OBJECT

public:
	ListTeachers(QWidget *parent, PluginManager *pluginManager);

private:
	QListView		*listView;
	DisplayTeacher	*displayer;
	QPushButton		*editButton;
	QPushButton		*deleteButton;
	QBoxLayout		*informationsLayout;
	PluginManager	*_pluginManager;

private slots:
	void			TeacherSelected(const QModelIndex &current, const QModelIndex &previous);
	void			TeacherAdded();
	void			TeacherEdited();
	void			TeacherDeleted();

signals:
	void			editTeacher(UserData *user);
};

#endif
