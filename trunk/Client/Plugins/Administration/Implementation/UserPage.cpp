#include "UserPage.h"
#include "UserModel.h"
#include "AdminModel.h"

UserPage::UserPage(TreeDataPlugin* tree, UserDataPlugin *_users)
{
    users = _users;
    mainLayout = new QHBoxLayout(this);
    userTree = new QTreeView();
    mainLayout->addWidget(userTree);
    //userTree->setModel(new UserModel(users->getAllUser()));
    userTree->setModel(new AdminModel(users->getAllUser(), tree->getNode(0)));
    connect(userTree, SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(ShowTreeMenu(const QPoint&)));
    connect(userTree->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(userSelected(QModelIndex)));
}

void UserPage::userSelected(const QModelIndex &nodeIndex)
{

}

void    UserPage::ShowTreeMenu(const QPoint& pnt)
{
}
