#include "UserPage.h"
#include "UserModel.h"
#include "AdminModel.h"
#include "FilterModel.h"
#include <QMenu>

UserPage::UserPage(TreeDataPlugin* tree, UserDataPlugin *_users)
{
    users = _users;
    usrPnl = 0;
    mainLayout = new QHBoxLayout(this);
    userTree = new QTreeView();
    mainLayout->addWidget(userTree);
    userTree->setContextMenuPolicy(Qt::CustomContextMenu);
    userTree->setMinimumWidth(150);
    FilterModel* fModel = new FilterModel(1, this);
    fModel->setSourceModel(new AdminModel(users->getAllUser(), tree->getNode(0)));
    userTree->setModel(fModel);
    //userTree->setModel(new AdminModel(users->getAllUser(), tree->getNode(0)));
    connect(userTree, SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(ShowTreeMenu(const QPoint&)));
    connect(userTree->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(userSelected(QModelIndex)));
}

void UserPage::userSelected(const QModelIndex &nodeIndex)
{
}

void    UserPage::ShowTreeMenu(const QPoint& pnt)
{
    TreeData* node = qobject_cast<TreeData*>(ckdData);
    QList<QAction *> actions;
    if (!node)
    {
        UserData* user = qobject_cast<UserData*>(ckdData);
        if (userTree->indexAt(pnt).isValid())
        {
                QAction *editUser = new QAction(QIcon(":/images/pencil.png"), tr("&Edit User..."), this);
                editUser->setShortcuts(QKeySequence::New);
                editUser->setStatusTip(tr("Edit an existing user"));
                connect(editUser, SIGNAL(triggered()), this, SLOT(editUser()));
                QAction *delUser = new QAction(QIcon(":/images/cross.png"), tr("&Delete User..."), this);
                delUser->setShortcuts(QKeySequence::DeleteEndOfWord);
                delUser->setStatusTip(tr("Delete an existing user"));
                connect(delUser, SIGNAL(triggered()), this, SLOT(delUser()));

                actions.append(editUser);
                actions.append(delUser);
        }
    }
    if (actions.count() > 0)
        QMenu::exec(actions, userTree->mapToGlobal(pnt));
}

void    UserPage::closePanel()
{
    if (usrPnl != NULL)
        usrPnl->close();
    usrPnl = 0;
}

void    UserPage::addUser()
{
    closePanel();
    usrPnl = new UserForm((TreeData*)ckdData,*users);
    mainLayout->removeItem(mainLayout->itemAt(1));
    mainLayout->setContentsMargins(2, 2, 2, 2);
    mainLayout->addWidget(usrPnl);
}


void    UserPage::editUser()
{
    closePanel();
    usrPnl = new UserForm(((UserData*)ckdData)->node(),(UserData*)ckdData ,*users);
    mainLayout->removeItem(mainLayout->itemAt(1));
    mainLayout->setContentsMargins(2, 2, 2, 2);
    mainLayout->addWidget(usrPnl);
}

void    UserPage::delUser()
{

}