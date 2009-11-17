#ifndef				__MANAGETEACHERS_H__
# define			__MANAGETEACHERS_H__

# include			<QWidget>

# include			<QBoxLayout>

# include			"../../../../../Common/PluginManager.h"
# include			"../../../../../Common/UserData.h"
# include			"ListTeachers.h"
# include			"EditTeacher.h"

class				ManageTeachers : public QWidget
{
	Q_OBJECT

public:
	ManageTeachers(QWidget *parent, PluginManager *pluginManager);

private:
	PluginManager	*_pluginManager;
	ListTeachers		*list;
	EditTeacher		*edit;
	QBoxLayout		*layout;

private slots:
	void			TeacherEdited(UserData *user);
	void			editExited();
};

#endif
