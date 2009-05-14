#ifndef USER_H
#define USER_H

#include <QObject>
#include <QHash>
#include <QByteArray>
#include <QDateTime>

#include "../Common/Defines.h"

class User : public QObject
{
  Q_OBJECT

public:
    User();
    ~User();

    enum Level { ROOT, ADMINISTRATOR, TEACHER, STUDENT, FAMILY, GUEST };

    void              login(const QString& _login, bool authSession, const QByteArray& _auth);
    void              renewSession(quint32 duration = DEFAULT_SESSION_LIFETIME*60);
    void              destroySession();
    void              logout();

    bool              isLoggedIn() const;
    quint32           getId() const;
    const QString     getUserName() const;
    Level             getLevel() const;
    const QByteArray& getSessionString() const;
    const QDateTime&  getSessionEnd() const;

    void              sendPacket(const QByteArray&);

private:
    quint32           id;
    QString           user;
    Level             level;
    QByteArray        sessionString;
    QDateTime         sessionEnd;

signals:
    void              sendPacketSignal(const QByteArray&);



//STATIC MEMBERS:
public:
    static User*               getUser(quint32 userId);
    static User*               getUser(QString login);
private:
    static QHash<quint32,User*> map;
};

#endif // USER_H
