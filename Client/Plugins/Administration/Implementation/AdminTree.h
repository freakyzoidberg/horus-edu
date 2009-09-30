#ifndef ADMINTREE_H
#define ADMINTREE_H

#include <QWidget>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QCalendarWidget>
#include <QtGui/QCheckBox>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QCalendarWidget>
#include <QTreeView>
#include "../../../../Common/TreeData.h"
#include "../../../../Common/UserData.h"
#include <QStackedWidget>
#include "UserForm.h"
#include "NodeInfo.h"

class AdminTree : public QWidget
{
    Q_OBJECT

    public:
        AdminTree(TreeDataPlugin* tree, UserDataPlugin *_users);
    private:
        QHBoxLayout *mainLayout;
        QTreeView *mainTree;
        QStackedWidget *groupBox;
        Data *ckdData;
        UserDataPlugin* users;
        NodeInfo*       ndPnl;
        void            closePanel();
        QMenu           *menu;
    private slots:
        void ShowTreeContextMenu(const QPoint& pnt);
        void nodeSelected(const QModelIndex &nodeIndex);
        void menuNode(QAction * action);
        //void editNode();
        //void delNode();
};

#endif // ADMINTREE_H
