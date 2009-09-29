#ifndef USERPAGE_H
#define USERPAGE_H

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

class UserPage : public QWidget
{
    Q_OBJECT

    public:
        UserPage(TreeDataPlugin* tree, UserDataPlugin *_users);
    private:
        QHBoxLayout *mainLayout;
        QTreeView *userTree;
        Data *ckdData;
        UserDataPlugin* users;
        void addUser();
        void editUser();
        void delUser();
        UserForm*       usrPnl;
        void            closePanel();
    private slots:
        void ShowTreeMenu(const QPoint& pnt);
        void userSelected(const QModelIndex &nodeIndex);
};

#endif // USERPAGE_H
