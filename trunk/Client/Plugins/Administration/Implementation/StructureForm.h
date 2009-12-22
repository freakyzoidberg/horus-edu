#ifndef				__STRUCTUREFORM_H__
# define			__STRUCTUREFORM_H__

# include			<QWidget>

# include			<QLabel>
# include			<QLineEdit>
# include			<QComboBox>

# include			"../../../../Common/UserData.h"

class				StructureForm : public QWidget
{
	Q_OBJECT

public:
	StructureForm(QWidget *parent, UserDataPlugin *userDataPlugin);
	QString			getName() const;
	UserData		*getTeacher() const;
	void			setTitle(QString title);
	void			setName(QString name);
	void			setTeacher(UserData *teacher);
	void			setTeacherVisibility(bool hidden);

private:
	QLabel			*titleLabel;
	QLineEdit		*nameField;
	QLabel			*teacherLabel;
	QComboBox		*teacherField;
	UserDataPlugin	*_userDataPlugin;

private slots:
	void			validate();
	void			cancel();

signals:
	void			validated();
};

#endif //			__STRUCTUREFORM_H__
