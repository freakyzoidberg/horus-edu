#ifndef USER_H
#define USER_H

#include <QObject>
#include <QMutex>
#include <QDebug>
#include <QByteArray>
#include <QCryptographicHash>

#include "Sql.h"

class User : public QObject
{

public:
    User();

    bool              loginPassword(const QByteArray& _login, const QByteArray& _sha1Pass);
    bool              loginSession (const QByteArray& _login, const QByteArray& _sessId);
    void              logout();
    const QByteArray& getSession();

private:
    QMutex      mutex;
    quint32     id;
    QByteArray  login;
    QByteArray  session;
};

#endif // USER_H
