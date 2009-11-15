#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QTabWidget>
#include "ManageStudents/ManageStudents.h"
#include "../../../../Common/TreeData.h"
#include "../../../../Common/UserData.h"
#include "../../../../Common/EventData.h"

class MainView : public QTabWidget
{
public:
    MainView();
    MainView(TreeDataPlugin *treeplugin, UserDataPlugin *userplugin, EventDataPlugin *eventplugin);
};

#endif // MAINVIEW_H
