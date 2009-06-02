#include "UserInfo.h"

UserInfo::UserInfo(QString login, QString session, int lvl)
{
    this->login = login;
    this->session = session;
    this->lvl   = lvl;
}

UserInfo::UserInfo()
{
}
