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