#ifndef USERFRAM_H
#define USERFRAM_H

#include "ui_UserFram.h"
#include "../../INetworkPlugin.h"
#include "../../../Common/Defines.h"
#include "../../ClientEvents.h"
#include <QHash>


class UserFram : public QFrame, private Ui::UserFram
{
    Q_OBJECT


    typedef void (UserFram::*requestFunction)(QVariantHash& response);

    public:
        explicit    UserFram(INetwork *reseau,QObject     *parent);
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
        void    clearForm();
        void    getTree();
        void    getTreeResponse(QVariantHash &response);
        void    getNodInfo();
        void    getNodInfoResponse(QVariantHash &response);
        void    deleteNode(QString idNode);
        void    moveNode(QString from, QString to);
        void    editNode(QString id, QString type, QString name, QString userId);
        void    editNodeResponse(QVariantHash &response);
        void    updateTree(QVariantHash tree);
        INetwork    *res;
        QObject     *parent;
        QHash<QString, QVariantHash> studentlist;
        QVariant         id;
        QHash<QString, QVariant>  sTree;
        QHash<QString, QVariant>  classes;
        void    fillStudentTree(QHash<QString, QVariant > &usertree, QHash<QString, QVariant > node, int nodeid);
    private slots:
        //! callback of the GetUsers button, it send an event to NetworkManager
        void    on_AddButton_clicked();
        void    on_CancelButton_clicked();
        void    on_SaveButton_clicked();
        void    on_DelButton_clicked();
    protected slots:
        void            itemClicked(QTreeWidgetItem*, int);
    signals:
        //! signal emmitted to send a packet
        void sender(const QString&);

};

#endif // USERFRAM_H
