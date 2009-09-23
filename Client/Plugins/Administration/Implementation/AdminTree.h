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

class AdminTree : public QWidget
{
    Q_OBJECT

    public:
        AdminTree(TreeDataPlugin* tree, UserDataPlugin *users);
    private:
        QVBoxLayout *mainLayout;
        QTreeView *mainTree;
        QStackedWidget *groupBox;
    private slots:
        void ShowTreeContextMenu(const QPoint& pnt);
        void nodeSelected(const QModelIndex &nodeIndex);
};

#endif // ADMINTREE_H
