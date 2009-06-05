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
        void    fillUserFram();
        INetwork    *res;
    private slots:
    //! callback of the GetUsers button, it send an event to NetworkManager
    void    on_AddButton_clicked();
    void    on_CancelButton_clicked();
    void    on_SaveButton_clicked();
    void    on_DelButton_clicked();


};

#endif // USERFRAM_H
