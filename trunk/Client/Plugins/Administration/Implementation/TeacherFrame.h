#ifndef TeacherFrame_H
#define TeacherFrame_H

#include "ui_TeacherFrame.h"
#include "../../../../Common/NetworkPlugin.h"
#include "../../../../Common/Defines.h"
#include <QHash>

class TeacherFrame : public QFrame, private Ui::TeacherFrame
{

    Q_OBJECT

    typedef void (TeacherFrame::*requestFunction)(QVariantHash& response);
    public:
         TeacherFrame();
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
        void    fillTeacherFrame();
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

        QObject     *parent;
        QHash<QString, QVariantHash> proflist;
        QVariant         id;
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

#endif // TeacherFrame_H
