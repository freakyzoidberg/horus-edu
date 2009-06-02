#ifndef USERINFO_H
#define USERINFO_H

#include <QObject>

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
