#ifndef				__EDIT_PARENT_H__
# define			__EDIT_PARENT_H__

# include			<QWidget>
# include			<QLineEdit>
# include			<QDateEdit>
# include			<QTextEdit>
# include			<QComboBox>

# include			"../../../../../Common/PluginManager.h"
# include			"../../../../../Common/UserData.h"

class				EditParent : public QWidget
{
	Q_OBJECT

public:
	EditParent(QWidget *parent, PluginManager *pluginManager, UserData *user = 0);

private:
	PluginManager	*_pluginManager;
	QLineEdit		*lastNameField;
	QLineEdit		*firstNameField;
	QLineEdit		*mailField;
	QLineEdit		*homePhoneField;
	QLineEdit		*workPhoneField;
	QLineEdit		*mobilePhoneField;
	QLineEdit		*occupationalCategoryField;
	QLineEdit		*occupationField;
	QDateEdit		*birthDateField;
	QTextEdit		*addressField;
	QComboBox		*genderField;
	QComboBox		*relationshipField;

private slots:
	void			saved();
	void			exited();
	void			reseted();

signals:
	void			exit();
};

#endif