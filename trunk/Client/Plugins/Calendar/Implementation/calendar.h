#ifndef CALENDAR_H
#define CALENDAR_H

#include <QIcon>
#include <QString>
#include <QHash>
#include <QCalendarWidget>

#include "../../../../Common/UserDataPlugin.h"
#include "../../../../Common/PluginManager.h"
#include "../../../../Common/TreeDataPlugin.h"
#include "../../../../Common/UserDataPlugin.h"
#include "../../../../Common/TreeData.h"
#include "../../../../Common/EventData.h"
#include "../../../../Common/EventDataPlugin.h"
#include "../../../DisplayablePlugin.h"

#include "CalendarMainFrame.h"
#include "panel.h"
#include "addeventwidget.h"
#include "CalendarWidget.h"

class Calendar : public DisplayablePlugin
{
Q_OBJECT
Q_INTERFACES(DisplayablePlugin)

public:
                            Calendar();
    const QString           pluginName() const;
    QWidget                 *getWidget();
    const QString           pluginVersion() const;
    QIcon                   getIcon() const;
    void                    load();

    inline const QString    getDisplayableName() const { return "Calendar"; }

 public slots:
     //called when a clicked on the tiny calendar occurs
    void                        dateChanged();
    void                    tabChanged(int);

private:
    TreeDataPlugin          *treePlugin;
    UserDataPlugin          *userPlugin;
    EventDataPlugin         *eventPlugin;
    Panel                   *_panel;
    CalendarWidget          *_googleCalendar;
    AddEventWidget          *_add;
    QCalendarWidget         *_tinyCalendar;
    int                     _currentIndex;
    QVector<CalendarMainFrame *> frames;
};

#endif // CALENDAR_H
