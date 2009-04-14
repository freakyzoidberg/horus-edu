#ifndef USER_H
#define USER_H

#include <QObject>
#include <QMutex>
#include <QMutexLocker>
#include <QDebug>
#include <QByteArray>
#include <QCryptographicHash>
#include <QTime>

#include "Sql.h"

class User : public QObject
{
  Q_OBJECT

public:
    User();
    ~User();

    enum              tState { INIT, LOGGED_OUT, LOGGED_IN };
    void              init();
    tState            getState();

    bool              loginPassword(const QByteArray& _login, const QByteArray& _sha1Pass);
    bool              loginSession (const QByteArray& _login, const QByteArray& _sessId);
    void              logout();
    const QByteArray& newSession();

private:
    QMutex        mutex;
    tState        state;
    quint32       id;
    QByteArray    login;
    QByteArray    session;
};

#endif // USER_H
