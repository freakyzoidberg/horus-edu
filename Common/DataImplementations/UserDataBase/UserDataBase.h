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
    void keyToStream(QDataStream& s);
	void dataToStream(QDataStream& s) const;
    void dataFromStream(QDataStream& s);
    QDebug operator<<(QDebug debug) const;
#ifdef HORUS_CLIENT
    QVariant data(int column, int role = Qt::DisplayRole) const;
#endif
#ifdef HORUS_SERVER
    //! Fill the current data with a defined key from teh database.
    void fillFromDatabase  (QSqlQuery&);
    //! Create this data into the database, and update the key.
    void createIntoDatabase(QSqlQuery&);
    //! Save the current data into the database.
    void saveIntoDatabase  (QSqlQuery&);
    //! Delete the current data from the database.
    void deleteFromDatabase(QSqlQuery&);
#endif

    //UserData Interface
    inline const QString    login() const { return _login; }
    inline const QDateTime  lastLogin() const { return _lastLogin; }
    inline bool             loggedIn() const { return _loggedIn; }

    inline const QString    name() const { return _name; }
    void                    setName(const QString name);

    void                    setPassword(const QString password);

    inline const QString    surname() const { return _surname; }
    void                    setSurname(const QString name);

    inline quint8           level() const { return _level; }
    void                    setLevel(quint8 level);

    inline bool             enabled() const { return _enabled; }
    void                    enable(bool enabled);

    inline TreeData*        node() const { return _node; }
    void                    setNode(TreeData* node);

    inline const QString    language() const { return _language; }
    void                    setLanguage(const QString language);

    inline const QDate    birthDate() const { return _birthDate; }
    void                    setBirthDate(const QDate birthDate);

    inline const QVariant    picture() const { return _picture; }
    void                    setPicture(const QVariant picture);

    inline const QString    address() const { return _address; }
    void                    setAddress(const QString address);

    inline const QString    phone() const { return _phone; }
    void                    setPhone(const QString phone);

    inline const QString    country() const { return _country; }
    void                    setCountry(const QString country);
#ifdef HORUS_SERVER
    //! Create a random key to be able to identify a user without the password.
    QByteArray newSession(QSqlQuery&, const QDateTime& end);
    //! Destroy the session generated to allow only password authentication.
    void destroySession(QSqlQuery&);
#endif

private:
    inline UserDataBase(quint32 userId, UserDataBasePlugin* plugin) : UserData(userId, (UserDataPlugin*)plugin) { _node = 0; }
    inline ~UserDataBase() {}

    quint8      _level;
    bool        _enabled;
    bool        _loggedIn;
    QString     _login;
    QByteArray  _password;
    TreeData*   _node;
    QString     _name;
    QString     _surname;
    QDateTime   _lastLogin;
    QString     _language;
    QDate   _birthDate;
    QVariant  _picture;
    QString     _address;
    QString     _phone;
    QString     _country;
#ifdef HORUS_SERVER
    void updateLastLogin(QSqlQuery&);
#endif
};

#endif // USERDATABASE_H
