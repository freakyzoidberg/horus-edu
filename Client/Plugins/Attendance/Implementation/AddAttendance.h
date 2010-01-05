#ifndef ADDATTENDANCE_H
#define ADDATTENDANCE_H

#include <QWidget>
#include <QWidget>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QListView>
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
#include "../../../../Common/ScheduleData.h"
#include "../../../../Common/AttendanceData.h"
#include <QSortFilterProxyModel>

class AddAttendance : public QWidget
{
        Q_OBJECT

        public:
            AddAttendance(QWidget *parent, TreeData *tree, UserData *_user, ScheduleDataPlugin *event, AttendanceDataPlugin *attendanceDataPlugin);
        private:
            QDateEdit           *dateAttendance;
            QHBoxLayout         *absLayout;
            QHBoxLayout         *buttonLayout;
            QVBoxLayout         *leftSide;
            QGridLayout         *rightSide;
            QLineEdit           *userName;
            QComboBox           *typeList;
            QListView           *userList;
            QCheckBox           *allCourse;
            QPushButton         *okButton;
            CourPanel           *cours;
            QSortFilterProxyModel *proxyModel;
            QFrame		*lessonFrame;
            QGridLayout         *lessonBottomLayout;
            QBoxLayout          *lessonMainLayout;
            QLabel		*lessonTitle;
            void                setupUi();
            void                fillCourse(ScheduleDataPlugin *event);
            QWidget		*getLessonsFrame();
            UserData            *user;
            TreeData            *node;
            AttendanceDataPlugin *_attendanceDataPlugin;
            ScheduleDataPlugin  *_scheduleDataPlugin;
        private slots:
            void                reseted();
            void                saved();
            void                exited();
            void                dChanged(const QDate &);
            void                allChecked(int);
    signals:
        void			exit();
};

#endif // ADDATTENDANCE_H
