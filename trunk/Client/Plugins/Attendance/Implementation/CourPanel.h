#ifndef COURPANEL_H
#define COURPANEL_H

#include <QWidget>
#include <QtGui/QCheckBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>
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
#include "../../../../Common/ScheduleData.h"
#include "../../../../Common/AttendanceData.h"


class InfosLesson
{
    public:
        InfosLesson(/*QString n, QTime s, QTime e, bool st*/)
        {
//            name = n, start = s, end = e, state = st;
        }
        QCheckBox   *state;
        QTimeEdit   *start;
        QTimeEdit   *end;
        QLineEdit   *name;
};

class CourPanel : public QWidget
{
    Q_OBJECT

    public:
        CourPanel(ScheduleData *schedule, QDate date);
        QVBoxLayout     *checkBoxs;

        QVBoxLayout     *nameBoxs;
        QHBoxLayout     *courLayout;
        //QLabel          *coursName;
        QCheckBox       *checkState;
        QLineEdit       *courseName;
        QTimeEdit       *sTime;
        QTimeEdit       *eTime;
        QCheckBox       *absenceCheck;
        QList<InfosLesson *> lessonList;
   private:
        void            getScheduleLesson(ScheduleData *schedule, int day);
        void            addLesson();
        QGridLayout     *lessonBottomLayout;
        QBoxLayout      *lessonMainLayout;
};

#endif // COURPANEL_H
