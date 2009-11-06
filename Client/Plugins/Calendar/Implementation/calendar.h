#ifndef CALENDAR_H
#define CALENDAR_H

#include <QIcon>
#include <QString>
#include <QHash>

#include "../../../../Common/UserDataPlugin.h"
#include "../../../../Common/PluginManager.h"
#include "../../../../Common/TreeDataPlugin.h"
#include "../../../../Common/UserDataPlugin.h"
#include "../../../../Common/TreeData.h"
# include "../../../DisplayablePlugin.h"

#include "CalendarMainFrame.h"

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

private:
    TreeDataPlugin          *treePlugin;
    UserDataPlugin          *userPlugin;
    EventDataPlugin         *eventPlugin;
};

#endif // CALENDAR_H
