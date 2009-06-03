#ifndef USERFRAM_H
#define USERFRAM_H

#include "ui_UserFram.h"
#include "../../INetworkPlugin.h"

class UserFram : public QFrame, private Ui::UserFram
{
    Q_OBJECT
    Q_DISABLE_COPY(UserFram)

    typedef void (UserFram::*requestFunction)(QVariantHash& response);

    public:
        explicit    UserFram(INetwork *reseau);
        void        readResponse(QVariantHash response);
    protected:
        virtual void changeEvent(QEvent *e);
        QHash<QByteArray,requestFunction> requestFunctions;
    private:
        void    changePasswordResponse(QVariantHash &response);
        void    listUsersResponse(QVariantHash &response);
        void    getUserInfoResponse(QVariantHash &response);
        void    setUserInfoResponse(QVariantHash &response);
        void    createNewUserResponse(QVariantHash &response);
        void    disableUserResponse(QVariantHash &response);
        void    changePassword();
        void    listUsers();
        void    getUserInfo();
        void    setUserInfo();
        void    createNewUser();
        void    disableUser();
        void    unknownResponse(QVariantHash &response);

};

#endif // USERFRAM_H
