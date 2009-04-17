#ifndef USER_H
#define USER_H

#include <QObject>
#include <QByteArray>

#include "ClientSocket.h"

class User : public QObject
{
  Q_OBJECT

public:
    User(ClientSocket* sock);
    ~User();

    void              login(const QString& _login, bool authSession, const QByteArray& _auth);
    const QByteArray& getSession();
    void              destroySession();

    void              sendPacket(const QByteArray&);

private:
    quint32           id;
    QString           user;
    QByteArray        session;
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
