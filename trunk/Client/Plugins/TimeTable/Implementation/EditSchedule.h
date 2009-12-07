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

class EditSchedule : public QWidget
{
    public:
        EditSchedule(PluginManager *pluginManager, int id, int type);
        inline QDate                getStart() {_startDate->selectedDate();}
        inline void                 setStart(QDate date) {_startDate->setSelectedDate(date);}
        inline QDate                getEnd() {_endDate->selectedDate();}
        inline void                 setEnd(QDate date) {_endDate->setSelectedDate(date);}
    private:
        PluginManager               *_pManager;
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
        void                        fillClasses(TreeDataPlugin *treeData);
        void                        fillForm(int id);
};

#endif // EDITSCHEDULE_H
