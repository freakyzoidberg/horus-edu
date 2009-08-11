#ifndef USERINFO_H
#define USERINFO_H

#include <QObject>
#include <QString>

class UserInfo : public QObject
{
    public:
        UserInfo(QString login, QString session, int lvl);
        UserInfo();
        QString     login;
        QString     session;
        int         lvl;
};

#endif // USERINFO_H
