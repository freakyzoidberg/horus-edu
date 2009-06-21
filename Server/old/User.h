#ifndef USER_H
#define USER_H

#include "../Common/UserData.h"
#include "../Common/Defines.h"

//! User object. one for each connexion. used to authenticate a user
class User : public UserData
{
  Q_OBJECT

public:
    User();
    ~User();

    //! check in the database the pair login/pass or login/session
    /*! if authSession = true: _auth is the session key
     *  else _auth is the password
     */
    void              login(const QString& _login, bool authSession, const QByteArray& _auth);
    //! create a new randow key for the session for a duration in parameter
    void              renewSession(quint32 duration = DEFAULT_SESSION_LIFETIME*60);
    //! remove the session key from the database and logout
    void              logout();
    //! re-initialize this object
    void              init();

    //! true if a user is loggued in , false otherwise
    bool              isLoggedIn() const;
    //! return the id of the user, 0 if not logged in
    quint32           getId() const;
    //! return the login of the user
    const QString     getUserName() const;
    //! return the level of the user
    UserLevel             getLevel() const;
    //! return the curent session string
    const QByteArray& getSessionString() const;
    //! return the end time of the session
    const QDateTime&  getSessionEnd() const;

    void              sendPacket(const QByteArray&) const;

private:
    quint32           id;
    QString           user;
    UserLevel         level;
    QByteArray        sessionString;
    QDateTime         sessionEnd;

signals:
    //! called by a module to send a packet to an logged-in user
    void              sendPacketSignal(const QByteArray&) const;



//STATIC MEMBERS:
public:
    //! static members to find a logged-in user
    static User*               getUser(quint32 userId);
    static User*               getUser(QString login);
private:
    //! list of logged-in users
    static QHash<quint32,User*> loggedIn;
};

#endif // USER_H
