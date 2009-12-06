#ifndef EDITSCHEDULEEVENT_H
#define EDITSCHEDULEEVENT_H

#include <QWidget>
#include "../../../../Common/ScheduleData.h"

class EditScheduleEvent : public QWidget
{
    public:
        EditScheduleEvent(PluginManager *pluginManager);
    private:
        PluginManager   *_pManager;
};

#endif // EDITSCHEDULEEVENT_H
