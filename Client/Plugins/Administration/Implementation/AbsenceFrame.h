#ifndef ABSENCEFRAME_H
#define ABSENCEFRAME_H

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
#include <QComboBox>
#include <QtGui/QCalendarWidget>
#include <QListView>
#include <QDateEdit>
#include "CourPanel.h"
#include "../../../../Common/TreeData.h"
#include "../../../../Common/UserData.h"
#include "../../../../Common/EventData.h"
#include <QSortFilterProxyModel>
#include "UserPerClass.h"

class AbsenceFrame : public QWidget
{
    Q_OBJECT

    public:
        AbsenceFrame(TreeDataPlugin *tree, UserDataPlugin *user, EventDataPlugin *event);
    private:
        QDateEdit           *dateAbsence;
        QHBoxLayout         *absLayout;
        QHBoxLayout         *buttonLayout;
        QVBoxLayout         *leftSide;
        QGridLayout         *rightSide;
        QLineEdit           *userName;
        QComboBox           *classList;
        QListView           *userList;
        QCheckBox           *allCourse;
        QPushButton         *okButton;
        QList<CourPanel *>  courList;
        QSortFilterProxyModel *proxyModel;
        void                setupUi();
        void                fillClass(TreeDataPlugin *tree);
        void                fillCourse(EventDataPlugin *event);
        UserDataPlugin      *user;
    private slots:
        void                nameChanged(const QString &text);
        void                classChanged( int index );
        void                okClicked();
        void                dChanged(const QDate &);
        void                allChecked(int);
};

#endif // ABSENCEFRAME_H
