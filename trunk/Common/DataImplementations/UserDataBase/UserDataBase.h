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
private:
    inline UserDataBase(quint32 userId, UserDataBasePlugin* plugin) : UserData(userId, (UserDataPlugin*)plugin) { }
    inline ~UserDataBase() {}

    QDateTime   birthDate;
    QByteArray  picture;
    QString     address;
    QString     phone;
    QString     country;
#ifdef HORUS_SERVER
    void updateLastLogin(QSqlQuery&);
#endif

public:
    //! Have to write his key into the stream to be able to identify this data with the server and the cache.
    void keyToStream(QDataStream& s);
    //! Have to write his data into the stream.
    /*! Called to:
     *  - Transfert this data between client and server.
     *  - Write to a local cache file.
     *  - Compare two data.
     */
    void dataToStream(QDataStream& s);
    //! Have to read his data from the stream.
    /*! Called to:
     *  - Transfert this data between client and server.
     *  - Read from a local cache file.
     */
    void dataFromStream(QDataStream& s);

    //! Usefull for debuging. Not mandatory but important.
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
    //! Create a random key to be able to identify a user without the password.
    QByteArray newSession(QSqlQuery&, const QDateTime& end);
    //! Destroy the session generated to allow only password authentication.
    void destroySession(QSqlQuery&);
#endif
};

#endif // USERDATABASE_H
