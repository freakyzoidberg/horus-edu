#include "UserDataBase.h"
#include "UserDataBasePlugin.h"
#include "../../PluginManager.h"
#include "../../TreeData.h"
#include "../../TreeDataPlugin.h"
#include <QCryptographicHash>

UserDataBase::UserDataBase(quint32 userId, UserDataBasePlugin* plugin) : UserData(userId, plugin)
{
	_studentClass = _plugin->pluginManager->findPlugin<TreeDataPlugin*>()->rootNode();
	connect(_studentClass, SIGNAL(removed()), this, SLOT(nodeRemoved()));
}

void UserDataBase::nodeRemoved()
{
	disconnect(this, SLOT(nodeRemoved()));
	_studentClass = _plugin->pluginManager->findPlugin<TreeDataPlugin*>()->rootNode();
	connect(_studentClass, SIGNAL(removed()), this, SLOT(nodeRemoved()));
}

void UserDataBase::keyToStream(QDataStream& s)
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
	  << _gender
	  << _occupation
	  << _proCategory
	  << _relationship
	  << _student->id();
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
	  >> studentId;

	disconnect(this, SLOT(nodeRemoved()));
	_studentClass = _plugin->pluginManager->findPlugin<TreeDataPlugin*>()->node(studentClassId);
	connect(_student, SIGNAL(removed()), this, SLOT(nodeRemoved()));

	_gender = (UserGender)gender;
	_student = _plugin->pluginManager->findPlugin<UserDataPlugin*>()->user(studentId);

    Data::dataFromStream(s);
}

QDebug UserDataBase::operator<<(QDebug debug) const
{
    return debug << dataType()
                 << status()
                 << _id
                 << _level
                 << _login
                 << _lastLogin
                 ;
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

	disconnect(this, SLOT(nodeRemoved()));
	_studentClass = node;
	connect(_studentClass, SIGNAL(removed()), this, SLOT(nodeRemoved()));
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
	_student = student;
}

#ifdef HORUS_CLIENT
#include <QIcon>
QVariant UserDataBase::data(int column, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (column == 1)
            return _id;
        if (column == 0)
            return _login;
        if (column == 2)
            return _name;
        if (column == 3)
            return _surname;
        if (column == 4)
            return _lastLogin;
    }
    else if (role == Qt::DecorationRole && column == 0)
    {
       if (level() == 2)
            return QIcon(":/boss.ico");
        else
            return QIcon(":/user.ico");
    }
    return QVariant();
}
#endif

#ifdef HORUS_SERVER
quint8 UserDataBase::serverRead()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("SELECT enabled,login,level,password,student_class,last_login,language,surname,name,birth_date,picture,address,phone1,phone2,phone3,country,gender,occupation,pro_category,relationship,student,mtime FROM user WHERE id=?;");
    query.addBindValue(_id);

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	if ( ! query.next())
		return NOT_FOUND;

	_enabled    = query.value(0).toBool();
	_login      = query.value(1).toString();
	_level      = (UserLevel)(query.value(2).toUInt());
	_password   = QByteArray::fromHex(query.value(3).toByteArray());
	_studentClass = _plugin->pluginManager->findPlugin<TreeDataPlugin*>()->node( query.value(4).toUInt() );
	_lastLogin  = query.value(5).toDateTime();
	_language   = query.value(6).toString();
	_surname    = query.value(7).toString();
	_name       = query.value(8).toString();
	_birthDate  = query.value(9).toDate();
	_picture    = query.value(10).toByteArray();
	_address    = query.value(11).toString();
	_phone1     = query.value(12).toString();
	_phone2     = query.value(13).toString();
	_phone3     = query.value(14).toString();
	_country    = query.value(15).toString();
	_gender     = (UserGender)(query.value(16).toUInt());
	_occupation = query.value(17).toString();
	_proCategory  = query.value(18).toString();
	_relationship = query.value(19).toString();
	_student    = _plugin->pluginManager->findPlugin<UserDataPlugin*>()->user( query.value(20).toUInt() );
	_lastChange = query.value(21).toDateTime();

	disconnect(this, SLOT(nodeRemoved()));
	connect(_studentClass, SIGNAL(removed()), this, SLOT(nodeRemoved()));
	_lastChange	= query.value(14).toDateTime();

	return NONE;
}

quint8 UserDataBase::serverCreate()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("INSERT INTO user (enabled,login,level,password,student_class,last_login,language,surname,name,birth_date,picture,address,phone1,phone2,phone3,country,gender,occupation,pro_category,relationship,student,mtime,passmail) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,ENCRYPT(?));");
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
	query.addBindValue( (_lastChange = QDateTime::currentDateTime()) );

	//passmail
	query.addBindValue(_login);

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}

	((UserDataBasePlugin*)_plugin)->_users.remove(_id);
	_id = query.lastInsertId().toUInt();
	((UserDataBasePlugin*)_plugin)->_users.insert(_id, this);

	return NONE;
}

quint8 UserDataBase::serverSave()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("UPDATE user SET enabled=?,login=?,level=?,password=?,student_class=?,last_login=?,language=?,surname=?,name=?,birth_date=?,picture=?,address=?,phone1=?,phone2=?,phone3=?,country=?,gender=?,occupation=?,pro_category=?,relationship=?,student=?,mtime=? WHERE id=?;");
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
	query.addBindValue( (_lastChange = QDateTime::currentDateTime()) );
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

quint8 UserDataBase::serverRemove()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("DELETE FROM user WHERE id=?;");
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

	query.prepare("UPDATE user SET session_key=?, session_end=? WHERE id=?;");
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
	query.prepare("UPDATE user SET session_key='', session_end='' WHERE id=?;");
    query.addBindValue(_id);

	if ( ! query.exec())
		qDebug() << query.lastError();
}

void UserDataBase::updateLastLogin()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("UPDATE user SET last_login=? WHERE id=?;");
    query.addBindValue(QDateTime::currentDateTime());
    query.addBindValue(_id);

	if ( ! query.exec())
		qDebug() << query.lastError();
}
#endif
