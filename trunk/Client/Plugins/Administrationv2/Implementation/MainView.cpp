#include "MainView.h"

MainView::MainView()
{
    this->addTab(new ManageStudents(),tr("Students"));
}

MainView::MainView(TreeDataPlugin *treeplugin, UserDataPlugin *userplugin, EventDataPlugin *eventplugin)
{
}
