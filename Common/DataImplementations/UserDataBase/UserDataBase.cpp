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
#include "UserDataBase.h"
#include "UserDataBasePlugin.h"
#include "../../PluginManager.h"
#include "../../TreeData.h"
#include "../../TreeDataPlugin.h"
#include <QCryptographicHash>

const char* UserDataBase::levelStrings[] = {
	"ROOT",
	"ADMINISTRATOR",
	"TEACHER",
	"STUDENT",
	"FAMILY",
	"GUEST",
	"NOBODY"
};

UserDataBase::UserDataBase(quint32 userId, UserDataBasePlugin* plugin) : UserData(userId, plugin)
{
	moveToThread(plugin->thread());
	_level = __LAST_LEVEL__;
	_enabled = false;
	_loggedIn = false;
	_gender = GENDER_UNKNOW;
	_repeatedYears = 0;
	_startYear = 0;
	_leaveYear = 0;
}

void UserDataBase::studentClassRemoved()
{
	disconnect(this, SLOT(studentClassRemoved()));
	_studentClass = _plugin->pluginManager->findPlugin<TreeDataPlugin*>()->rootNode();
	connect(_studentClass, SIGNAL(removed()), this, SLOT(studentClassRemoved()));
}

void UserDataBase::keyToStream(QDataStream& s) const
{
    s << _id;
}

void UserDataBase::dataToStream(QDataStream& s) const
{
	s << _enabled
	  << _login
	  << _level
	  << _password
	  << _studentClass->id()
	  << _lastLogin
	  << _language
	  << _surname
      << _name
      << _birthDate
      << _picture
      << _address
	  << _phone1
	  << _phone2
	  << _phone3
	  << _country
	  << (quint8)_gender
	  << _occupation
	  << _proCategory
	  << _relationship
	  << _student->id()
	  << _mail
	  << _subscriptionReason
	  << _repeatedYears
	  << _startYear
	  << _leaveYear
	  << _followUp
	  << _comment
	  << _bornPlace
	  << _nbrBrothers
	  << _socialInsuranceNbr
	  << _diploma
	  << _contract;
	Data::dataToStream(s);
}

void UserDataBase::dataFromStream(QDataStream& s)
{
	quint32 studentClassId;
	quint32 studentId;
	quint8	gender;
	s >> _enabled
	  >> _login
	  >> _level
	  >> _password
	  >> studentClassId
	  >> _lastLogin
	  >> _language
	  >> _surname
	  >> _name
	  >> _birthDate
	  >> _picture
	  >> _address
	  >> _phone1
	  >> _phone2
	  >> _phone3
	  >> _country
	  >> gender
	  >> _occupation
	  >> _proCategory
	  >> _relationship
	  >> studentId
	  >> _mail
	  >> _subscriptionReason
	  >> _repeatedYears
	  >> _startYear
	  >> _leaveYear
	  >> _followUp
	  >> _comment
	  >> _bornPlace
	  >> _nbrBrothers
	  >> _socialInsuranceNbr
	  >> _diploma
	  >> _contract;

	disconnect(this, SLOT(studentClassRemoved()));
	_studentClass = _plugin->pluginManager->findPlugin<TreeDataPlugin*>()->node(studentClassId);
	connect(_student, SIGNAL(removed()), this, SLOT(studentClassRemoved()));

	_gender = (UserGender)gender;

	disconnect(_student, SIGNAL(removed()), this, SLOT(remove()));
	_student = _plugin->pluginManager->findPlugin<UserDataPlugin*>()->user(studentId);
	connect(_student, SIGNAL(removed()), this, SLOT(remove()));

    Data::dataFromStream(s);
}

bool UserDataBase::canChange(UserData* user) const
{
	if (user->level() <= LEVEL_ADMINISTRATOR || user == _plugin->pluginManager->currentUser())
		return true;
	return false;
}

bool UserDataBase::canAccess(UserData*) const
{
//	if (user->level() <= LEVEL_ADMINISTRATOR || user == _plugin->pluginManager->currentUser())
//		return true;
//	return false;
	return true;
}

QDebug UserDataBase::operator<<(QDebug debug) const
{
    return debug << dataType()
                 << status()
                 << _id
				 << (UserLevel)_level
                 << _login
                 << _lastLogin
                 ;
}

const QList<Data*> UserDataBase::dependsOfCreatedData() const
{
	QList<Data*> list;
	list.append(_studentClass);
	return list;
}

void UserDataBase::setName(const QString name)
{
	QMutexLocker M(&mutex);
    _name = name;
}

void UserDataBase::setPassword(const QString password)
{    
	QMutexLocker M(&mutex);
    _password = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha1);
}

void UserDataBase::setSurname(const QString surname)
{
	QMutexLocker M(&mutex);
    _surname = surname;
}

void UserDataBase::setLevel(quint8 level)
{
	QMutexLocker M(&mutex);
    _level = level;
}

void UserDataBase::setEnable(bool enabled)
{
	QMutexLocker M(&mutex);
    _enabled = enabled;
}

void UserDataBase::setStudentClass(TreeData* node)
{
	QMutexLocker M(&mutex);
	disconnect(this, SLOT(studentClassRemoved()));
	_studentClass = node;
	connect(_studentClass, SIGNAL(removed()), this, SLOT(studentClassRemoved()));
}

void UserDataBase::setLanguage(const QString language)
{
	QMutexLocker M(&mutex);
    _language = language;
}

void UserDataBase::setCountry(const QString country)
{
	QMutexLocker M(&mutex);
    _country = country;
}

void UserDataBase::setAddress(const QString address)
{
	QMutexLocker M(&mutex);
    _address = address;
}

void UserDataBase::setBirthDate(const QDate birthDate)
{
	QMutexLocker M(&mutex);
    _birthDate = birthDate;
}

void UserDataBase::setPicture(const QVariant picture)
{
	QMutexLocker M(&mutex);
    _picture = picture;
}

void UserDataBase::setPhone1(const QString phone)
{
	QMutexLocker M(&mutex);
	_phone1 = phone;
}

void UserDataBase::setPhone2(const QString phone)
{
	QMutexLocker M(&mutex);
	_phone2 = phone;
}

void UserDataBase::setPhone3(const QString phone)
{
	QMutexLocker M(&mutex);
	_phone3 = phone;
}

void UserDataBase::setGender(UserGender gender)
{
	QMutexLocker M(&mutex);
	_gender = gender;
}

void UserDataBase::setOccupation(const QString occupation)
{
	QMutexLocker M(&mutex);
	_occupation = occupation;
}

void UserDataBase::setProCategory(const QString category)
{
	QMutexLocker M(&mutex);
	_proCategory = category;
}

void UserDataBase::setRelationship(const QString relationship)
{
	QMutexLocker M(&mutex);
	_relationship = relationship;
}

void UserDataBase::setStudent(UserData* student)
{
	QMutexLocker M(&mutex);
	disconnect(_student, SIGNAL(removed()), this, SLOT(removed()));
	_student = student;
	connect(_student, SIGNAL(removed()), this, SLOT(removed()));
}

void UserDataBase::setMail(const QString mail)
{
	QMutexLocker M(&mutex);
	_mail = mail;
}

void UserDataBase::setSubscriptionReason(const QString reason)
{
	QMutexLocker M(&mutex);
	_subscriptionReason = reason;
}

void UserDataBase::setRepeatedYears(quint8 nbYears)
{
	QMutexLocker M(&mutex);
	_repeatedYears = nbYears;
}

void UserDataBase::setStartYear(quint16 startYear)
{
	QMutexLocker M(&mutex);
	_startYear = startYear;
}

void UserDataBase::setLeaveYear(quint16 year)
{
	QMutexLocker M(&mutex);
	_leaveYear = year;
}

void UserDataBase::setFollowUp(const QString followUp)
{
	QMutexLocker M(&mutex);
	_followUp = followUp;
}

void UserDataBase::setComment(const QString comment)
{
	QMutexLocker M(&mutex);
	_comment = comment;
}

void UserDataBase::setBornPlace(const QString bornPlace)
{
	QMutexLocker M(&mutex);
	_bornPlace = bornPlace;
}

void UserDataBase::setNbrBrothers(quint8 nbrBrothers)
{
	QMutexLocker M(&mutex);
	_nbrBrothers = nbrBrothers;
}

void UserDataBase::setSocialInsuranceNbr(const QString socialInsuranceNbr)
{
	QMutexLocker M(&mutex);
	_socialInsuranceNbr = socialInsuranceNbr;
}

void UserDataBase::setDiploma(const QString diploma)
{
	QMutexLocker M(&mutex);
	_diploma = diploma;
}

void UserDataBase::setContract(const QString contract)
{
	QMutexLocker M(&mutex);
	_contract = contract;
}

#ifdef HORUS_CLIENT
#include <QIcon>
QVariant UserDataBase::data(int column, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (column == 0)
			return _surname + ' ' + _name;
		if (column == 1)
			return _login;
    }
    else if (role == Qt::DecorationRole && column == 0)
    {
       if (level() == 2)
            return QIcon(":/boss.ico");
        else
            return QIcon(":/user.ico");
    }
	else if (role == FILTER_ROLE && column == 0)
		return levelStrings[_level];

	return QVariant();
}
#endif

#ifdef HORUS_SERVER
quint8 UserDataBase::serverRead()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("SELECT`enabled`,`login`,`level`,`password`,`student_class`,`last_login`,`language`,`surname`,`name`,`birth_date`,`picture`,`address`,`phone1`,`phone2`,`phone3`,`country`,`gender`,`occupation`,`pro_category`,`relationship`,`student`,`mail`,`subscription_reason`,`repeated_years`,`start_year`,`leave_year`,`follow_up`,`comment`,`born_place`,`nbr_brothers`,`social_insurance_nbr`,`diploma`,`contract`,`mtime`FROM`user`WHERE`id`=?;");
    query.addBindValue(_id);

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	if ( ! query.next())
		return NOT_FOUND;

	_enabled		= query.value(0).toBool();
	_login			= query.value(1).toString();
	_level			= (UserLevel)(query.value(2).toUInt());
	_password		= QByteArray::fromHex(query.value(3).toByteArray());
	_studentClass	= _plugin->pluginManager->findPlugin<TreeDataPlugin*>()->node( query.value(4).toUInt() );
	_lastLogin		= query.value(5).toDateTime();
	_language		= query.value(6).toString();
	_surname		= query.value(7).toString();
	_name			= query.value(8).toString();
	_birthDate		= query.value(9).toDate();
	_picture		= query.value(10).toByteArray();
	_address		= query.value(11).toString();
	_phone1			= query.value(12).toString();
	_phone2			= query.value(13).toString();
	_phone3			= query.value(14).toString();
	_country		= query.value(15).toString();
	_gender			= (UserGender)(query.value(16).toUInt());
	_occupation		= query.value(17).toString();
	_proCategory	= query.value(18).toString();
	_relationship	= query.value(19).toString();
	_student		= _plugin->pluginManager->findPlugin<UserDataPlugin*>()->user( query.value(20).toUInt() );
	_mail			= query.value(21).toString();
	_subscriptionReason	= query.value(22).toString();
	_repeatedYears	= query.value(23).toUInt();
	_startYear		= query.value(24).toUInt();
	_leaveYear		= query.value(25).toUInt();
	_followUp		= query.value(26).toString();
	_comment		= query.value(27).toString();
	_bornPlace		= query.value(28).toString();
	_nbrBrothers	= query.value(29).toUInt();
	_socialInsuranceNbr = query.value(30).toString();
	_diploma		= query.value(31).toString();
	_contract		= query.value(32).toString();
	_lastChange		= query.value(33).toDateTime();

	disconnect(this, SLOT(studentClassRemoved()));
	connect(_studentClass, SIGNAL(removed()), this, SLOT(studentClassRemoved()));
	_lastChange	= query.value(14).toDateTime();

	return NONE;
}

quint8 UserDataBase::serverCreate()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("INSERT INTO`user`(`enabled`,`login`,`level`,`password`,`student_class`,`last_login`,`language`,`surname`,`name`,`birth_date`,`picture`,`address`,`phone1`,`phone2`,`phone3`,`country`,`gender`,`occupation`,`pro_category`,`relationship`,`student`,`mail`,`subscription_reason`,`repeated_years`,`start_year`,`leave_year`,`follow_up`,`comment`,`born_place`,`nbr_brothers`,`social_insurance_nbr`,`diploma`,`contract`,`mtime`,`passmail`)VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,ENCRYPT(?));");
	query.addBindValue(_enabled);
	query.addBindValue(_login);
    query.addBindValue(_level);
	query.addBindValue(_password.toHex());
	query.addBindValue(_studentClass->id());
	query.addBindValue(_lastLogin);
	query.addBindValue(_language);
	query.addBindValue(_surname);
    query.addBindValue(_name);
    query.addBindValue(_birthDate);
    query.addBindValue(_picture);
    query.addBindValue(_address);
	query.addBindValue(_phone1);
	query.addBindValue(_phone2);
	query.addBindValue(_phone3);
	query.addBindValue(_country);
	query.addBindValue(_gender);
	query.addBindValue(_occupation);
	query.addBindValue(_proCategory);
	query.addBindValue(_relationship);
	query.addBindValue(_student->id());
	query.addBindValue(_mail);
	query.addBindValue(_subscriptionReason);
	query.addBindValue(_repeatedYears);
	query.addBindValue(_startYear);
	query.addBindValue(_leaveYear);
	query.addBindValue(_followUp);
	query.addBindValue(_comment);
	query.addBindValue(_bornPlace);
	query.addBindValue(_nbrBrothers);
	query.addBindValue(_socialInsuranceNbr);
	query.addBindValue(_diploma);
	query.addBindValue(_contract);
	query.addBindValue( (_lastChange = QDateTime::currentDateTime()) );
	query.addBindValue(_login);//passmail

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}

	_id = query.lastInsertId().toUInt();

	return NONE;
}

quint8 UserDataBase::serverSave()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("UPDATE`user`SET`enabled`=?,`login`=?,`level`=?,`password`=?,`student_class`=?,`last_login`=?,`language`=?,`surname`=?,`name`=?,`birth_date`=?,`picture`=?,`address`=?,`phone1`=?,`phone2`=?,`phone3`=?,`country`=?,`gender`=?,`occupation`=?,`pro_category`=?,`relationship`=?,`student`=?,`mail`=?,`subscription_reason`=?,`repeated_years`=?,`start_year`=?,`leave_year`=?,`follow_up`=?,`comment`=?,`born_place`=?,`nbr_brothers`=?,`social_insurance_nbr`=?,`diploma`=?,`contract`=?,`mtime`=? WHERE`id`=?;");
	query.addBindValue(_enabled);
	query.addBindValue(_login);
    query.addBindValue(_level);
	query.addBindValue(_password.toHex());
	query.addBindValue(_studentClass->id());
	query.addBindValue(_lastLogin);
	query.addBindValue(_language);
	query.addBindValue(_surname);
    query.addBindValue(_name);
    query.addBindValue(_birthDate);
    query.addBindValue(_picture);
    query.addBindValue(_address);
	query.addBindValue(_phone1);
	query.addBindValue(_phone2);
	query.addBindValue(_phone3);
	query.addBindValue(_country);
	query.addBindValue(_gender);
	query.addBindValue(_occupation);
	query.addBindValue(_proCategory);
	query.addBindValue(_relationship);
	query.addBindValue(_student->id());
	query.addBindValue(_mail);
	query.addBindValue(_subscriptionReason);
	query.addBindValue(_repeatedYears);
	query.addBindValue(_startYear);
	query.addBindValue(_leaveYear);
	query.addBindValue(_followUp);
	query.addBindValue(_comment);
	query.addBindValue(_bornPlace);
	query.addBindValue(_nbrBrothers);
	query.addBindValue(_socialInsuranceNbr);
	query.addBindValue(_diploma);
	query.addBindValue(_contract);
	query.addBindValue( (_lastChange = QDateTime::currentDateTime()) );
    query.addBindValue(_id);

    if ( ! query.exec())
    {
		qDebug() << query.lastError();
		return DATABASE_ERROR;
    }
	return NONE;
}

quint8 UserDataBase::serverRemove()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("DELETE FROM`user`WHERE`id`=?;");
    query.addBindValue(_id);

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	if ( ! query.numRowsAffected())
		return NOT_FOUND;

	return NONE;
}

QByteArray UserDataBase::newSession(const QDateTime& end)
{
	QMutexLocker M(&mutex);
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	QByteArray session;
    qsrand(QTime::currentTime().msec() + _id);
    for (int i = 0; i < SESSION_WORD_SIZE; i++)
        session[i] = qrand();

	query.prepare("UPDATE`user`SET`session_key`=?,`session_end`=? WHERE`id`=?;");
    query.addBindValue(session.toHex());
    query.addBindValue(end);
    query.addBindValue(_id);

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return QByteArray();
	}
	if ( ! query.numRowsAffected())
		return QByteArray();

    return session;
}

void UserDataBase::destroySession()
{
	QMutexLocker M(&mutex);
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("UPDATE`user`SET`session_key`='',`session_end`=''WHERE`id`=?;");
    query.addBindValue(_id);

	if ( ! query.exec())
		qDebug() << query.lastError();
}

void UserDataBase::updateLastLogin()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("UPDATE`user`SET`last_login`=? WHERE`id`=?;");
    query.addBindValue(QDateTime::currentDateTime());
    query.addBindValue(_id);

	if ( ! query.exec())
		qDebug() << query.lastError();
}
#endif
