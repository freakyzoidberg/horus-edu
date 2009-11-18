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
//	EditParent(QWidget *parent, PluginManager *pluginManager, UserData *user = 0);
        EditParent(QWidget *parent, UserData *user);
        QString             getlastN() { return lastNameField->text(); }
        QString             getfirsN() { return firstNameField->text(); }
        QString             getmail() { return mailField->text(); }
        QString             gethomeP() { return homePhoneField->text(); }
        QString             getworkP() { return workPhoneField->text(); }
        QString             getmobileP() { return mobilePhoneField->text(); }
        QString             getoccuC() { return occupationalCategoryField->text(); }
        QString             getoccuField() { return occupationField->text(); }
        QDate               getbirthD() { return birthDateField->date(); }
        QString             getaddr() { return addressField->toPlainText(); }
        int                 getgender() { return genderField->itemData(genderField->currentIndex()).toInt(); }
        QString             getrela() { return relationshipField->itemData(relationshipField->currentIndex()).toString(); }
private:
//	PluginManager	*_pluginManager;
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
	UserData		*_user;

//private slots:
//	void			saved();
//	void			exited();
//	void			reseted();
//
//signals:
//	void			exit();
};

#endif
