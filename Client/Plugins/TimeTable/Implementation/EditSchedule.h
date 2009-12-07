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
        EditSchedule(PluginManager *pluginManager);
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

};

#endif // EDITSCHEDULE_H
