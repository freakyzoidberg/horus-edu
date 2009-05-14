#ifndef USER_H
#define USER_H

#include <QObject>
#include <QByteArray>
#include <QDateTime>

#include "ClientSocket.h"
#include "../Common/Defines.h"

class User : public QObject
{
  Q_OBJECT

public:
    User(ClientSocket* sock);
    ~User();

    enum Level { ROOT, ADMINISTRATOR, TEACHER, STUDENT, FAMILY, GUEST };

    void              login(const QString& _login, bool authSession, const QByteArray& _auth);
    void              renewSession(quint32 duration = DEFAULT_SESSION_LIFETIME*60);
    void              destroySession();
    const QByteArray& getSessionString();
    const QDateTime&  getSessionEnd();

    void              sendPacket(const QByteArray&);

private:
    quint32           id;
    QString           user;
    Level             level;
    QByteArray        sessionString;
    QDateTime         sessionEnd;
    ClientSocket*     socket;

signals:
    void              sendPacketSignal(const QByteArray&);



    //STATIC MEMBERS:
public:
    static User*               getUser(quint32 userId);
    static User*               getUser(QString login);
private:
    static QMap<quint32, User*> map;
};

#endif // USER_H
