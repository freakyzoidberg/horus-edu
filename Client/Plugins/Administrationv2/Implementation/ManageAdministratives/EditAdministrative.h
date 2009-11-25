#ifndef				__EDITADMINISTRATIVE_H__
# define			__EDITADMINISTRATIVE_H__

# include			<QWidget>
# include			<QLineEdit>
# include			<QDateEdit>
# include			<QTextEdit>
# include			<QComboBox>

# include			"../../../../../Common/PluginManager.h"
# include			"../../../../../Common/UserData.h"

class				EditAdministrative : public QWidget
{
	Q_OBJECT

public:
	EditAdministrative(QWidget *parent, PluginManager *pluginManager, UserData *user = 0);

private:
	PluginManager	*_pluginManager;
	QLineEdit		*lastNameField;
	QLineEdit		*firstNameField;
	QLineEdit		*mailField;
	QLineEdit		*homePhoneField;
	QLineEdit		*workPhoneField;
	QLineEdit		*mobilePhoneField;
	QDateEdit		*birthDateField;
	QLineEdit		*birthPlaceField;
	QTextEdit		*addressField;
	QComboBox		*genderField;
	QLineEdit		*socialInsuranceNbrField;
	QTextEdit		*diplomaField;
	QTextEdit		*contractField;
	UserData		*_user;

private slots:
	void			saved();
	void			exited();
	void			reseted();

signals:
	void			exit();
};

#endif