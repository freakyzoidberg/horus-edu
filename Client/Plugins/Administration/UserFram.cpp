#include "UserFram.h"

UserFram::UserFram(QWidget *parent) : QFrame(parent)
{
    setupUi(this);
    requestFunctions["changePassword"]  = &UserFram::changePasswordResponse;
    requestFunctions["listUsers"]       = &UserFram::listUsersResponse;
    requestFunctions["getUserInfo"]     = &UserFram::getUserInfoResponse;
    requestFunctions["setUserInfo"]     = &UserFram::setUserInfoResponse;
    requestFunctions["createNewUser"]   = &UserFram::createNewUserResponse;
    requestFunctions["disableUser"]     = &UserFram::disableUserResponse;
}

void    UserFram::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}

void    UserFram::changePassword()
{
    QVariantHash request;

    request["Request"] =  "changePassword";
    request["password"] =  "";
    request["OldPassword"]=  "";
}

void    UserFram::listUsers()
{
    QVariantHash request;

    request["Request"] =  "listUsers";
}

void    UserFram::getUserInfo()
{
    QVariantHash request;

    request["Request"] =  "getUserInfo";
}

void    UserFram::setUserInfo()
{
/*    QVariantHash user;
    user["Request"] =  "setUserInfo";
    user["id"]         = ;
    user["login"]      = ;
    user["id_tree"]    = ;
    user["level"]      = ;
    user["last_login"] = ;
    user["address"]    = ;
    user["phone"]      = ;
    user["country"]    = ;
    user["language"]   = ;*/
}

void    UserFram::createNewUser()
{
    /*    QVariantHash user;
    user["Request"] =  "CreateNewUser";
    user["id"]         = ;
    user["login"]      = ;
    user["id_tree"]    = ;
    user["level"]      = ;
    user["last_login"] = ;
    user["address"]    = ;
    user["phone"]      = ;
    user["country"]    = ;
    user["language"]   = ;*/
}

void    UserFram::disableUser()
{
    QVariantHash request;

    request["Request"] =  "disableUser";
}

void    UserFram::readResponse(QVariantHash response)
{
    (this->*requestFunctions.value(response["Request"].toByteArray(),
                                   &UserFram::unknownResponse))
                                   (response);
}

void    UserFram::unknownResponse(QVariantHash &response)
{

}

void    UserFram::changePasswordResponse(QVariantHash &response)
{

}

void    UserFram::listUsersResponse(QVariantHash &response)
{

}

void    UserFram::getUserInfoResponse(QVariantHash &response)
{

}

void    UserFram::setUserInfoResponse(QVariantHash &response)
{

}

void    UserFram::createNewUserResponse(QVariantHash &response)
{

}

void    UserFram::disableUserResponse(QVariantHash &response)
{

}
