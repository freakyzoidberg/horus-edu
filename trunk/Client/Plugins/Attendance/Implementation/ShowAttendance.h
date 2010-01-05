#ifndef SHOWATTENDANCE_H
#define SHOWATTENDANCE_H

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

class InfosAttendance
{
    public:
        InfosAttendance(/*QString n, QTime s, QTime e, bool st*/)
        {
//            name = n, start = s, end = e, state = st;
        }
        QLineEdit   *type;
        QDateEdit   *date;
        QTimeEdit   *start;
        QTimeEdit   *end;
        QLineEdit   *name;
        QPushButton *del;
};

class ShowAttendance : public QWidget
{
    Q_OBJECT

    public:
        ShowAttendance(QWidget *parent, UserData *user, AttendanceDataPlugin *attendanceDataPlugin);
    private:
        QFrame		*lessonFrame;
        QGridLayout         *lessonBottomLayout;
        QBoxLayout          *lessonMainLayout;
        QLabel		*lessonTitle;
        QWidget     *getAttendancesFrame();
        QList<InfosAttendance *> attendanceList;
        AttendanceDataPlugin *_attendanceDataPlugin;
        UserData            *_user;
    signals:
        void			exit();
};

#endif // SHOWATTENDANCE_H
