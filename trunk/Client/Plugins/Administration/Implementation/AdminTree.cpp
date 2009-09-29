#include "AdminTree.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QBuffer>
#include <QMenu>
#include <QRadioButton>
#include "AdminModel.h"


AdminTree::AdminTree(TreeDataPlugin* tree, UserDataPlugin *_users)
{
    users = _users;
    ndPnl = 0;
    usrPnl = 0;
    mainLayout = new QHBoxLayout(this);
    mainTree = new QTreeView();
    mainLayout->addWidget(mainTree);
    mainTree->setModel(new AdminModel(users->getAllUser(), tree->getNode(0)));
    //mainTree->expandAll();
    mainTree->setMinimumWidth(200);
    mainTree->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(mainTree, SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(ShowTreeContextMenu(const QPoint&)));
    //mainTree->clearSelection();
    connect(mainTree->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(nodeSelected(QModelIndex)));
    groupBox = new QStackedWidget();
    mainLayout->setStretch(1, 1);
    //closePanel();
}

void    AdminTree::closePanel()
{
    if (ndPnl != NULL)
        ndPnl->close();
    if (usrPnl != NULL)
        usrPnl->close();
    ndPnl = 0;
    usrPnl = 0;
}

void AdminTree::nodeSelected(const QModelIndex &nodeIndex)
{
    ckdData = ((Data*)nodeIndex.internalPointer());
    TreeData* node = qobject_cast<TreeData*>((Data*)nodeIndex.internalPointer());
    if (!node)
    {
        UserData* user = qobject_cast<UserData*>((Data*)nodeIndex.internalPointer());
        editUser();
        return ;
    }
    else
    {
        editNode();
    }

}

void    AdminTree::ShowTreeContextMenu(const QPoint& pnt)
{
    TreeData* node = qobject_cast<TreeData*>(ckdData);
    QList<QAction *> actions;
    if (!node)
    {
        UserData* user = qobject_cast<UserData*>(ckdData);
        if (mainTree->indexAt(pnt).isValid())
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
    else
    {
          if (mainTree->indexAt(pnt).isValid())
          {
                QAction *addUser = new QAction(QIcon(":/images/add.png"), tr("&Add User..."), this);
                addUser->setShortcuts(QKeySequence::AddTab);
                addUser->setStatusTip(tr("Add a new user"));
                connect(addUser, SIGNAL(triggered()), this, SLOT(addUser()));
                QAction *addNode = new QAction(QIcon(":/images/addButton.png"), tr("&Add Node..."), this);
                addNode->setShortcuts(QKeySequence::Open);
                addNode->setStatusTip(tr("Add a new node"));
                connect(addNode, SIGNAL(triggered()), this, SLOT(addNode()));
                QAction *editNode = new QAction(QIcon(":/images/editButton.png"), tr("&Edit Node..."), this);
                editNode->setShortcuts(QKeySequence::Find);
                editNode->setStatusTip(tr("Edit an existing node"));
                connect(editNode, SIGNAL(triggered()), this, SLOT(editNode()));
                QAction *delNode = new QAction(QIcon(":/images/delButton.png"), tr("&Delete Node..."), this);
                delNode->setShortcuts(QKeySequence::Delete);
                delNode->setStatusTip(tr("Open an existing node"));
                connect(delNode, SIGNAL(triggered()), this, SLOT(delNode()));

                actions.append(addNode);
                actions.append(addUser);
                actions.append(editNode);
                actions.append(delNode);
          }
    }
    if (actions.count() > 0)
        QMenu::exec(actions, mainTree->mapToGlobal(pnt));
}

void    AdminTree::addNode()
{
    closePanel();
    ndPnl = new NodeInfo(*((TreeData*)ckdData), 2, *users);
    mainLayout->removeItem(mainLayout->itemAt(1));
    mainLayout->setContentsMargins(2, 2, 2, 2);
    mainLayout->addWidget(ndPnl);
}

void    AdminTree::editNode()
{
    closePanel();
    ndPnl = new NodeInfo(*((TreeData*)ckdData), 1, *users);
    mainLayout->removeItem(mainLayout->itemAt(1));
    mainLayout->setContentsMargins(2, 2, 2, 2);
    mainLayout->addWidget(ndPnl);
}

void    AdminTree::delNode()
{
    ((TreeData*)ckdData)->recursRemove();
}

void    AdminTree::addUser()
{
    closePanel();
    usrPnl = new UserForm((TreeData*)ckdData,*users);
    mainLayout->removeItem(mainLayout->itemAt(1));
    mainLayout->setContentsMargins(2, 2, 2, 2);
    mainLayout->addWidget(usrPnl);
}


void    AdminTree::editUser()
{
    closePanel();
    usrPnl = new UserForm(((UserData*)ckdData)->node(),(UserData*)ckdData ,*users);
    mainLayout->removeItem(mainLayout->itemAt(1));
    mainLayout->setContentsMargins(2, 2, 2, 2);
    mainLayout->addWidget(usrPnl);
}

void    AdminTree::delUser()
{

}
