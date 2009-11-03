#ifndef CALENDARCORE_H
#define CALENDARCORE_H

#include <QHash>

#include "../../../../Common/TreeDataPlugin.h"
#include "../../../../Common/TreeData.h"
#include "../../../../Common/UserDataPlugin.h"
#include "../../../../Common/UserData.h"

class CalendarCore
{
public:
    static  CalendarCore        *CalendarCoreInstance(TreeDataPlugin *tree = NULL,
                                                      UserDataPlugin *user = NULL);
    QHash<quint32, TreeData *>  *getNodeOfType(QString type);
    QStringList                 usersName(QHash<quint32, TreeData *> *);

private:
                                CalendarCore(TreeDataPlugin *, UserDataPlugin *);
    static  CalendarCore        *_instance;

    TreeDataPlugin              *tree;
    UserDataPlugin              *users;
};

#endif // CALENDARCORE_H
