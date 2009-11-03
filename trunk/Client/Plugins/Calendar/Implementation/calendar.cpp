#include <QHash>

#include "calendar.h"
#include "CalendarMainFrame.h"
#include "CalendarCore.h"

Calendar::Calendar()
{
    treePlugin = NULL;
    userPlugin = NULL;
}

const QString   Calendar::pluginName()    const
{
    return "Calendar";
}

const QString   Calendar::pluginVersion() const
{
    return "0.001b.17/10/2009.18h19min";
}

QWidget *Calendar::getWidget()
{
    CalendarMainFrame *frame = new CalendarMainFrame(this->treePlugin, this->userPlugin);
    return frame;
}

void Calendar::load()
{
    treePlugin = pluginManager->findPlugin<TreeDataPlugin*>();
    userPlugin = pluginManager->findPlugin<UserDataPlugin *>();

    Plugin::load();
    CalendarCore::CalendarCoreInstance(treePlugin, userPlugin);
}

QIcon   Calendar::getIcon() const
{
    return (QIcon("agenda.png"));
}
