#include "AdminTree.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QBuffer>
#include <QMenu>
#include <QRadioButton>
#include "AdminModel.h"

AdminTree::AdminTree(TreeDataPlugin* tree, UserDataPlugin *users)
{
    mainLayout = new QVBoxLayout(this);
    mainTree = new QTreeView();
    mainLayout->addWidget(mainTree);
    mainTree->setModel(new AdminModel(users->getAllUser(), tree->getNode(0)));

    mainTree->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(mainTree, SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(ShowTreeContextMenu(const QPoint&)));
    connect(mainTree->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(nodeSelected(QModelIndex)));
    groupBox = new QStackedWidget();
    mainLayout->setStretch(1, 1);
    mainLayout->setContentsMargins(2, 2, 2, 2);
    mainLayout->addWidget(groupBox);
}

void AdminTree::nodeSelected(const QModelIndex &nodeIndex)
{
    TreeData* node = qobject_cast<TreeData*>((Data*)nodeIndex.internalPointer());
    if (!node)
    {
        UserData* user = qobject_cast<UserData*>((Data*)nodeIndex.internalPointer());
        qDebug() << user->login();
        return ;
    }
    else
    {
        qDebug() << node->id();
    }
    QGroupBox *grpBox = new QGroupBox(tr("Edit :"));
    QRadioButton *radio1 = new QRadioButton(tr("&Radio button 1"));
    QRadioButton *radio2 = new QRadioButton(tr("R&adio button 2"));
    QRadioButton *radio3 = new QRadioButton(tr("Ra&dio button 3"));

    radio1->setChecked(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    vbox->addWidget(radio3);
    vbox->addStretch(1);
    grpBox->setLayout(vbox);
    groupBox->addWidget(grpBox);
}

void    AdminTree::ShowTreeContextMenu(const QPoint& pnt)
{
  QList<QAction *> actions;
  if (mainTree->indexAt(pnt).isValid())
  {
        QAction *actAdd = new QAction(tr("Ajouter"), this);
        QAction *actEdit = new QAction(tr("Edit"), this);
        QAction *actRen = new QAction(tr("Rename"), this);
        QAction *actDel = new QAction(tr("Delete"), this);
        actions.append(actAdd);
        actions.append(actEdit);
        actions.append(actRen);
        actions.append(actDel);

  }
  if (actions.count() > 0)
    QMenu::exec(actions, mainTree->mapToGlobal(pnt));
}
