#ifndef USER_H
#define USER_H

#include <QString>
#include <QMutex>
#include <QByteArray>
#include <QCryptographicHash>

class User
{

public:
    User();

    enum              stateType{ CONECTING, LOGININ };
    stateType         state() const;

    bool              loginPassword(const QString& _login, const QByteArray& _sha1Pass);
    bool              loginSession (const QString& _login, const QByteArray& _sessId);
    void              logout();
    const QByteArray& getSession();

private:
    stateType   stateValue;
    QMutex      mutex;
    QString     login;
    QByteArray  session;
};

#endif // USER_H
