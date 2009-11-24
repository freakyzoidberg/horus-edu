#ifndef USERDATA_H
#define USERDATA_H

#include <QByteArray>
#include <QDateTime>
#include "Data.h"
#include "UserDataPlugin.h"

//! enumerate the differents Level of users
enum UserLevel { LEVEL_ROOT, LEVEL_ADMINISTRATOR, LEVEL_TEACHER, LEVEL_STUDENT, LEVEL_FAMILY, LEVEL_GUEST, __LAST_LEVEL__ };
enum UserGender { GENDER_MALE, GENDER_FEMALE, GENDER_UNKNOW };

class TreeData;
class UserData : public Data
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerData)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientData)
#endif

public:
	inline quint32			id() const { return _id; }

	virtual const QString	login() const = 0;
	virtual const QDateTime	lastLogin() const = 0;
	virtual bool			loggedIn() const = 0;

	virtual const QString	name() const = 0;
	virtual void			setName(const QString name) = 0;

	virtual void			setPassword(const QString password) = 0;

	virtual const QString	surname() const = 0;
	virtual void			setSurname(const QString name) = 0;

	virtual quint8			level() const = 0;
	virtual void			setLevel(quint8 level) = 0;

	virtual bool			enable() const = 0;
	virtual void			setEnable(bool enabled) = 0;

	virtual TreeData*		studentClass() const = 0;
	virtual void			setStudentClass(TreeData* node) = 0;

	virtual const QString	language() const = 0;
	virtual void			setLanguage(const QString language) = 0;

	virtual const QDate		birthDate() const = 0;
	virtual void			setBirthDate(const QDate birthDate) = 0;

	virtual const QVariant	picture() const = 0;
	virtual void			setPicture(const QVariant picture) = 0;

	virtual const QString	address() const = 0;
	virtual void			setAddress(const QString address) = 0;

	virtual const QString	phone1() const = 0;
	virtual void			setPhone1(const QString phone) = 0;
	virtual const QString	phone2() const = 0;
	virtual void			setPhone2(const QString phone) = 0;
	virtual const QString	phone3() const = 0;
	virtual void			setPhone3(const QString phone) = 0;

	virtual const QString	country() const = 0;
	virtual void			setCountry(const QString country) = 0;

	virtual UserGender		gender() const = 0;
	virtual void			setGender(UserGender) = 0;

	virtual const QString	occupation() const = 0;
	virtual void			setOccupation(const QString occupation) = 0;

	virtual const QString	proCategory() const = 0;
	virtual void			setProCategory(const QString category) = 0;

	virtual const QString	relationship() const = 0;
	virtual void			setRelationship(const QString relationship) = 0;

	virtual UserData*		student() const = 0;
	virtual void			setStudent(UserData* student) = 0;

	virtual const QString	mail() const = 0;
	virtual void			setMail(const QString mail) = 0;

	virtual const QString	subscriptionReason() const = 0;
	virtual void			setSubscriptionReason(const QString reason) = 0;

	virtual quint8			repeatedYears() const = 0;
	virtual void			setRepeatedYears(quint8) = 0;

	virtual quint16			startYear() const = 0;
	virtual void			setStartYear(quint16) = 0;

	virtual quint16			leaveYear() const = 0;
	virtual void			setLeaveYear(quint16) = 0;

	virtual const QString	followUp() const = 0;
	virtual void			setFollowUp(const QString followUp) = 0;

	virtual const QString	comment() const = 0;
	virtual void			setComment(const QString comment) = 0;

	virtual const QString	bornPlace() const = 0;
	virtual void			setBornPlace(const QString comment) = 0;

	virtual quint8			nbrBrothers() const = 0;
	virtual void			setNbrBrothers(quint8) = 0;

	virtual const QString	socialInsuranceNbr() const = 0;
	virtual void			setSocialInsuranceNbr(const QString comment) = 0;

	virtual const QString	diploma() const = 0;
	virtual void			setDiploma(const QString comment) = 0;

	virtual const QString	contract() const = 0;
	virtual void			setContract(const QString comment) = 0;


#ifdef HORUS_SERVER
    //! Create a random key to be able to identify a user without the password.
	virtual QByteArray newSession(const QDateTime& end) = 0;
    //! Destroy the session generated to allow only password authentication.
	virtual void destroySession() = 0;
#endif

protected:
	inline					UserData(quint32 id, UserDataPlugin* plugin) : Data(plugin) { _id = id; }
	virtual inline			~UserData() {}
	quint32					_id;
};

#ifdef HORUS_SERVER
typedef UserData ServerUserData;
Q_DECLARE_INTERFACE(ServerUserData, "net.horus.ServerUserData/1.0");
#endif
#ifdef HORUS_CLIENT
typedef UserData ClientUserData;
Q_DECLARE_INTERFACE(ClientUserData, "net.horus.ClientUserData/1.0");
#endif

#endif // USERDATA_H
