#ifndef UserFrame_H
#define UserFrame_H

#include "ui_UserFrame.h"
#include "../../../NetworkPlugin.h"
#include "../../../../Common/Defines.h"
#include "../../ClientEvents.h"
#include <QHash>


class UserFrame : public QFrame, private Ui::UserFrame
{
    Q_OBJECT


    typedef void (UserFrame::*requestFunction)(QVariantHash& response);

    public:
            UserFrame();
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
        void    fillUserFrame();
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
        void sender(const QString&, PluginPacket *packet);

};

#endif // UserFrame_H
