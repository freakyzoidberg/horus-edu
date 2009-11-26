/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "UserPage.h"
#include <QMenu>

UserPage::UserPage(TreeDataPlugin* _tree, UserDataPlugin *_users)
{
    users = _users;
    tree = _tree;
    usrPnl = 0;
    mainLayout = new QHBoxLayout(this);
    userTree = new QTreeView();
    mainLayout->addWidget(userTree);
    userTree->setContextMenuPolicy(Qt::CustomContextMenu);
    userTree->setMinimumWidth(150);
    userTree->setAnimated(true);
    userTree->setAutoExpandDelay(500);
    FilterModel* fModel = new FilterModel(1, this);
	fModel->setSourceModel(new AdminModel(users->allUser(), tree->rootNode()));
    userTree->setModel(fModel);

    //userTree->setModel(new AdminModel(users->getAllUser(), tree->getNode(0)));
    connect(userTree, SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(ShowTreeMenu(const QPoint&)));
    connect(userTree->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(userSelected(QModelIndex)));
}

void UserPage::userSelected(const QModelIndex &nodeIndex)
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
        closePanel();
        _index = nodeIndex;
    }
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
    else
    {
        QAction *addUser = new QAction(QIcon(":/images/add.png"), tr("&Add User..."), this);
        addUser->setShortcuts(QKeySequence::Open);
        addUser->setStatusTip(tr("Add a new user"));
        connect(addUser, SIGNAL(triggered()), this, SLOT(addUser()));

        actions.append(addUser);
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
    usrPnl = new UserForm((TreeData*)ckdData,users, this);
    mainLayout->removeItem(mainLayout->itemAt(1));
    mainLayout->setContentsMargins(2, 2, 2, 2);
    mainLayout->addWidget(usrPnl);
}


void    UserPage::editUser()
{
    closePanel();
    usrPnl = new UserForm(((UserData*)ckdData)->studentClass(),(UserData*)ckdData ,users, this);
    mainLayout->removeItem(mainLayout->itemAt(1));
    mainLayout->setContentsMargins(2, 2, 2, 2);
    mainLayout->addWidget(usrPnl);
}

void    UserPage::delUser()
{
}

void    UserPage::resetPage()
{
    FilterModel* fModel = new FilterModel(1, this);
	fModel->setSourceModel(new AdminModel(users->allUser(), tree->rootNode()));
    userTree->setModel(fModel);
    connect(userTree->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(userSelected(QModelIndex)));
}
