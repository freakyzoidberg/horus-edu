#ifndef				__EDITPARENT_H__
# define			__EDITPARENT_H__

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
	//EditParent(QWidget *parent, PluginManager *pluginManager, UserData *user = 0);
	EditParent(UserData *father = 0, UserData *mother = 0);
	QString             getlastN() { return lastNameFatherField->text(); }
	QString             getlastN2() { return lastNameMotherField->text(); }
	QString             getfirsN() { return firstNameFatherField->text(); }
	QString             getfirsN2() { return firstNameMotherField->text(); }
	QString             getmail() { return mailField->text(); }
	QString             gethomeP() { return homePhoneField->text(); }
	QString             getworkP() { return workPhoneField->text(); }
	QString             getmobileP() { return mobilePhoneField->text(); }
	QString             getoccuC() { return occupationalCategoryFatherField->text(); }
	QString             getoccuC2() { return occupationalCategoryMotherField->text(); }
	QString             getoccuField() { return occupationFatherField->text(); }
	QString             getoccuField2() { return occupationMotherField->text(); }
	QString             getaddr() { return addressField->toPlainText(); }
	QString             getrela() { return relationshipField->itemData(relationshipField->currentIndex()).toString(); }

private:
	//PluginManager	*_pluginManager;
	QLineEdit		*lastNameFatherField;
	QLineEdit		*lastNameMotherField;
	QLineEdit		*firstNameFatherField;
	QLineEdit		*firstNameMotherField;
	QLineEdit		*mailField;
	QLineEdit		*homePhoneField;
	QLineEdit		*workPhoneField;
	QLineEdit		*mobilePhoneField;
	QLineEdit		*occupationalCategoryFatherField;
	QLineEdit		*occupationalCategoryMotherField;
	QLineEdit		*occupationFatherField;
	QLineEdit		*occupationMotherField;
	QTextEdit		*addressField;
	QComboBox		*relationshipField;
	UserData		*_user;
	void                    setupUi();

//private slots:
//	void			saved();
//	void			exited();
//	void			reseted();
//
//signals:
//	void			exit();
};

#endif
