#ifndef DAYLESSONS_H
#define DAYLESSONS_H

#include <QWidget>
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
#include "../../../../Common/UserData.h"
#include "../../../../Common/ScheduleData.h"

class InfosLesson
{
    public:
        InfosLesson()
        {
        }
        QTimeEdit   *start;
        QTimeEdit   *end;
        QLineEdit   *name;
};

class DayLessons : public QWidget
{
    Q_OBJECT

    public:
        DayLessons(ScheduleDataPlugin *schedule, UserData *user);
        QList<InfosLesson *> lessonList;
};

#endif // DAYLESSONS_H
