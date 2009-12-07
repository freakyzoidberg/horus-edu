#ifndef EDITSCHEDULE_H
#define EDITSCHEDULE_H

#include <QWidget>
#include <QComboBox>
#include <QCalendarWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFrame>
#include <QLabel>
#include "EditException.h"
#include "../../../../Common/ScheduleData.h"
#include "../../../../Common/TreeData.h"
#include "../../../../Common/ScheduleDataPlugin.h"

class EditSchedule : public QWidget
{
    Q_OBJECT

    public:
        EditSchedule(ScheduleDataPlugin *sd, TreeDataPlugin *td, int id, int type);
        inline QDate                getStart() {_startDate->selectedDate();}
        inline void                 setStart(QDate date) {_startDate->setSelectedDate(date);}
        inline QDate                getEnd() {_endDate->selectedDate();}
        inline void                 setEnd(QDate date) {_endDate->setSelectedDate(date);}
    private:
        ScheduleDataPlugin          *sdp;
        TreeDataPlugin              *tdp;
        QComboBox                   *_classList;
        QCalendarWidget             *_startDate;
        QCalendarWidget             *_endDate;
        QVBoxLayout                 *vLayout;
        QHBoxLayout                 *titleLayout;
        QHBoxLayout                 *hLayout;
        QHBoxLayout                 *hLayout2;
        QList<EditException *>      *_excpList;
        QPushButton                 *_addException;
        QFrame                      *line;
        void                        fillClasses();
        void                        fillForm(int id);
    private slots:
        void                        addException();
};

#endif // EDITSCHEDULE_H
