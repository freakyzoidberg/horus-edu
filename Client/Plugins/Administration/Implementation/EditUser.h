/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef				__EDITUSER_H__
# define			__EDITUSER_H__

# include			<QWidget>

# include			<QLineEdit>
# include			<QDateEdit>
# include			<QTextEdit>
# include			<QSpinBox>
# include			<QComboBox>

# include			"../../../../Common/TreeData.h"
# include			"../../../../Common/UserData.h"

class				EditUser : public QWidget
{
	Q_OBJECT

public:
	EditUser(QWidget *parent, UserDataPlugin *userDataPlugin, int userLevel, TreeData *node = 0, UserData *user = 0);

private:
	UserDataPlugin	*_userDataPlugin;
	int				_userLevel;
	TreeData		*_node;
	UserData		*_user;
	UserData		*father;
	UserData		*mother;

	QWidget			*getPersonnalFrame();
	QWidget			*getContactFrame();
	QWidget			*getProfessionalFrame();
	QWidget			*getStudiesFrame();
	QWidget			*getParentFrame();
	QWidget			*getParentContactFrame();

	QLineEdit		*lastNameField;
	QLineEdit		*firstNameField;
	QDateEdit		*birthDateField;
	QLineEdit		*birthPlaceField;
	QComboBox		*genderField;
	QSpinBox		*siblingsField;
	QTextEdit		*addressField;
	QLineEdit		*mailField;
	QLineEdit		*homePhoneField;
	QLineEdit		*mobilePhoneField;
	QLineEdit		*workPhoneField;
	QLineEdit		*socialInsuranceNbrField;
	QTextEdit		*diplomaField;
	QTextEdit		*contractField;
	QLineEdit		*referentField;
	QTextEdit		*motiveField;
	QLineEdit		*financialHelpsField;
	QSpinBox		*startYearField;
	QSpinBox		*leaveYearField;
	QSpinBox		*repeatedYearsField;
	QSpinBox		*skippedYearsField;
	QTextEdit		*followUpField;
	QLineEdit		*fatherLastNameField;
	QLineEdit		*motherLastNameField;
	QLineEdit		*fatherFirstNameField;
	QLineEdit		*motherFirstNameField;
	QLineEdit		*fatherOccupationField;
	QLineEdit		*motherOccupationField;
	QComboBox		*relationshipField;
	QTextEdit		*fatherAddressField;
	QTextEdit		*motherAddressField;
	QLineEdit		*fatherEmailField;
	QLineEdit		*motherEmailField;
	QLineEdit		*fatherHomePhoneField;
	QLineEdit		*motherHomePhoneField;
	QLineEdit		*fatherMobilePhoneField;
	QLineEdit		*motherMobilePhoneField;
	QLineEdit		*fatherWorkPhoneField;
	QLineEdit		*motherWorkPhoneField;

private slots:
	void			saved();
	void			exited();
	void			reseted();

signals:
	void			exit();
};

#endif
