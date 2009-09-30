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
    menu = new QMenu("Menu", this);
    connect(menu, SIGNAL(triggered(QAction *)), this, SLOT(menuNode(QAction *)));
    //closePanel();
}

void    AdminTree::closePanel()
{
    if (ndPnl != NULL)
        ndPnl->close();
    ndPnl = 0;
}

void AdminTree::nodeSelected(const QModelIndex &nodeIndex)
{
    ckdData = ((Data*)nodeIndex.internalPointer());
    TreeData* node = qobject_cast<TreeData*>((Data*)nodeIndex.internalPointer());
    if (node)
    {
        QAction *editNode = new QAction(QIcon(":/images/editButton.png"), tr("&Edit..."), this);
        QStringList tmpList;
        tmpList << "Edit";
        editNode->setData(tmpList);
        menuNode(editNode);
    }

}

void    AdminTree::ShowTreeContextMenu(const QPoint& pnt)
{
    TreeData* node = qobject_cast<TreeData*>(ckdData);
    QList<QAction *> actions;
    if (node)
    {
          if (mainTree->indexAt(pnt).isValid())
          {
                 QStringList tmpList;
                if (node->type() == "ROOT")
                {
                    QAction *addGrp = new QAction(QIcon(":/images/addButton.png"), tr("&Add Group..."), this);
                    addGrp->setShortcuts(QKeySequence::Open);
                    addGrp->setStatusTip(tr("Add a new group"));
                    tmpList << "Add" << "GROUP";
                    addGrp->setData(tmpList);
                    tmpList.clear();
                    //connect(addGrp, SIGNAL(triggered(QAction *)), this, SLOT(addNode(QAction *)));
                    QAction *addCls = new QAction(QIcon(":/images/addButton.png"), tr("&Add Classes..."), this);
                    addCls->setShortcuts(QKeySequence::Open);
                    addCls->setStatusTip(tr("Add a new group of classes"));
                    tmpList << "Add" << "CLASSES";
                    addCls->setData(tmpList);
                    //connect(addCls, SIGNAL(triggered(QAction *)), this, SLOT(addNode(QAction *)));
                    actions.append(addGrp);
                    actions.append(addCls);
                    tmpList.clear();
                }
                else if (node->type() == "CLASSES")
                {
                    QAction *addGrd = new QAction(QIcon(":/images/addButton.png"), tr("&Add Grades..."), this);
                    addGrd->setShortcuts(QKeySequence::Open);
                    addGrd->setStatusTip(tr("Add a new grade"));
                    tmpList << "Add" << "GRADE";
                    addGrd->setData(tmpList);
                    //connect(addGrd, SIGNAL(triggered(QAction *)), this, SLOT(addNode(QAction *)));
                    actions.append(addGrd);
                    tmpList.clear();
                }
                else if (node->type() == "GRADE")
                {
                    QAction *addSbj = new QAction(QIcon(":/images/addButton.png"), tr("&Add Subject..."), this);
                    addSbj->setShortcuts(QKeySequence::Open);
                    addSbj->setStatusTip(tr("Add a new Subject"));
                    tmpList << "Add" << "SUBJECT";
                    addSbj->setData(tmpList);
                    //connect(addSbj, SIGNAL(triggered(QAction *)), this, SLOT(addNode(QAction *)));
                    actions.append(addSbj);
                    tmpList.clear();
                }
                QAction *editNode = new QAction(QIcon(":/images/editButton.png"), tr("&Edit..."), this);
                editNode->setShortcuts(QKeySequence::Find);
                editNode->setStatusTip(tr("Edit an existing item"));
                tmpList << "Edit";
                editNode->setData(tmpList);
                tmpList.clear();
                //connect(editNode, SIGNAL(triggered()), this, SLOT(editNode()));
                QAction *delNode = new QAction(QIcon(":/images/delButton.png"), tr("&Delete..."), this);
                delNode->setShortcuts(QKeySequence::Delete);
                delNode->setStatusTip(tr("Delete selected item"));
                tmpList << "Del";
                delNode->setData(tmpList);
                tmpList.clear();
                //connect(delNode, SIGNAL(triggered()), this, SLOT(delNode()));

                actions.append(editNode);
                actions.append(delNode);
          }
    }
    if (actions.count() > 0)
    {
        foreach (QAction *a, actions)
            menu->addAction(a);
        menu->exec(mainTree->mapToGlobal(pnt));
        //QMenu::exec(actions, mainTree->mapToGlobal(pnt));
    }
}

void    AdminTree::menuNode(QAction * action)
{
    menu->clear();
    closePanel();
    if (action->data().toStringList().at(0) == "Add")
    {
        ndPnl = new NodeInfo(*((TreeData*)ckdData), 2, *users, action->data().toStringList().at(1), *this);
        mainLayout->removeItem(mainLayout->itemAt(1));
        mainLayout->setContentsMargins(2, 2, 2, 2);
        mainLayout->addWidget(ndPnl);
    }
    else if (action->data().toStringList().at(0) == "Edit")
    {
        ndPnl = new NodeInfo(*((TreeData*)ckdData), 1, *users, "", *this);
        mainLayout->removeItem(mainLayout->itemAt(1));
        mainLayout->setContentsMargins(2, 2, 2, 2);
        mainLayout->addWidget(ndPnl);
    }
    else
    {
        ((TreeData*)ckdData)->recursRemove();
        mainTree->reset();
    }
}

//void    AdminTree::editNode()
//{
//    closePanel();
//    ndPnl = new NodeInfo(*((TreeData*)ckdData), 1, *users, "");
//    mainLayout->removeItem(mainLayout->itemAt(1));
//    mainLayout->setContentsMargins(2, 2, 2, 2);
//    mainLayout->addWidget(ndPnl);
//}
//
//void    AdminTree::delNode()
//{
//    ((TreeData*)ckdData)->recursRemove();
//}



