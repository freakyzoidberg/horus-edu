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
#ifndef USERDATABASE_H
#define USERDATABASE_H

#ifdef HORUS_SERVER
    #include <QtSql>
#endif
#ifdef HORUS_CLIENT
    #include <QVariant>
#endif
#include <QByteArray>
#include <QDateTime>
#include "../../Defines.h"
#include "../../UserData.h"
#include "UserDataBasePlugin.h"

class UserDataBase : public UserData
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerUserData ServerData)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientUserData ClientData)
#endif

  friend class UserDataBasePlugin;

public:
    // Data Interface
	void					keyToStream(QDataStream& s) const;
	void					dataToStream(QDataStream& s) const;
	void					dataFromStream(QDataStream& s);

	bool					canChange(UserData* user) const;
	bool					canAccess(UserData* user) const;

	const QList<Data*>		dependsOfCreatedData() const;

	QDebug					operator<<(QDebug debug) const;
#ifdef HORUS_CLIENT
	QVariant				data(int column, int role = Qt::DisplayRole) const;
#endif
#ifdef HORUS_SERVER
	quint8					serverRead();
	quint8					serverCreate();
	quint8					serverSave();
	quint8					serverRemove();
#endif

    //UserData Interface
	inline const QString	login() const { return _login; }
	inline const QDateTime	lastLogin() const { return _lastLogin; }
	inline bool				loggedIn() const { return _loggedIn; }

	inline const QString	name() const { return _name; }
	void					setName(const QString name);

	void					setPassword(const QString password);

	inline const QString	surname() const { return _surname; }
	void					setSurname(const QString name);

	inline quint8			level() const { return _level; }
	void					setLevel(quint8 level);

	inline bool				enable() const { return _enabled; }
	void					setEnable(bool enabled);

	inline TreeData*		studentClass() const { return _studentClass; }
	void					setStudentClass(TreeData* node);

	inline const QString	language() const { return _language; }
	void					setLanguage(const QString language);

	inline const QDate		birthDate() const { return _birthDate; }
	void					setBirthDate(const QDate birthDate);

	inline const QVariant	picture() const { return _picture; }
	void					setPicture(const QVariant picture);

	inline const QString	address() const { return _address; }
	void					setAddress(const QString address);

	inline const QString	phone1() const { return _phone1; }
	void					setPhone1(const QString phone);
	inline const QString	phone2() const { return _phone2; }
	void					setPhone2(const QString phone);
	inline const QString	phone3() const { return _phone3; }
	void					setPhone3(const QString phone);

	inline const QString	country() const { return _country; }
	void					setCountry(const QString country);

	inline UserGender		gender() const { return _gender; }
	void					setGender(UserGender);

	inline const QString	occupation() const { return _occupation; }
	void					setOccupation(const QString occupation);

	inline const QString	proCategory() const { return _proCategory; }
	void					setProCategory(const QString category);

	inline const QString	relationship() const { return _relationship; }
	void					setRelationship(const QString relationship);

	inline UserData*		student() const { return _student; }
	void					setStudent(UserData* student);

	inline const QString	mail() const { return _mail; }
	void					setMail(const QString mail);

	inline const QString	subscriptionReason() const { return _subscriptionReason; }
	void					setSubscriptionReason(const QString reason);

	inline quint8			repeatedYears() const { return _repeatedYears; }
	void					setRepeatedYears(quint8 nbYears);

	inline quint16			startYear() const { return _startYear; }
	void					setStartYear(quint16);

	inline quint16			leaveYear() const { return _leaveYear; }
	void					setLeaveYear(quint16 year);

	inline const QString	followUp() const { return _followUp; }
	void					setFollowUp(const QString followUp);

	inline const QString	comment() const { return _comment; }
	void					setComment(const QString comment);

	inline const QString	bornPlace() const { return _bornPlace; }
	void					setBornPlace(const QString comment);

	inline quint8			nbrBrothers() const {return _nbrBrothers; }
	void					setNbrBrothers(quint8);

	inline const QString	socialInsuranceNbr() const {return _socialInsuranceNbr; }
	void					setSocialInsuranceNbr(const QString comment);

	inline const QString	diploma() const {return _diploma; }
	void					setDiploma(const QString comment);

	inline const QString	contract() const {return _contract; }
	void					setContract(const QString comment);

        const QString	mailPassord()const {return _mailpassword;}
        void			setMailPassword(const QString password);

private:
	UserDataBase(quint32 userId, UserDataBasePlugin* plugin);
	~UserDataBase() {}

	quint8					_level;
	bool					_enabled;
	bool					_loggedIn;
	QString					_login;
	QByteArray				_password;
	TreeData*				_studentClass;
	QString					_name;
	QString					_surname;
	QDateTime				_lastLogin;
	QString					_language;
	QDate					_birthDate;
	QVariant				_picture;
	QString					_address;
	QString					_phone1;
	QString					_phone2;
	QString					_phone3;
	QString					_country;
	UserGender				_gender;
	QString					_occupation;
	QString					_proCategory;
	QString					_relationship;
	UserData*				_student;
	QString					_mail;
	QString					_subscriptionReason;
	quint8					_repeatedYears;
	quint16					_startYear;
	quint16					_leaveYear;
	QString					_followUp;
	QString					_comment;
	QString					_bornPlace;
	quint8					_nbrBrothers;
	QString					_socialInsuranceNbr;
	QString					_diploma;
	QString					_contract;

	QString					_mailpassword;

	static const char*		levelStrings[];
private slots:
	void					studentClassRemoved();
	void					studentRemoved();
};

#endif // USERDATABASE_H
