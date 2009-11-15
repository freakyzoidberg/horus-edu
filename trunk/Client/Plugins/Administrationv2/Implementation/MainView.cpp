#include "MainView.h"

MainView::MainView()
{

}

MainView::MainView(TreeDataPlugin *treeplugin, UserDataPlugin *userplugin, EventDataPlugin *eventplugin)
{
    this->addTab(new ManageStudents(),tr("Students"));
}
