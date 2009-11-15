#include "MainView.h"
#include  "ManageClasses/AdmAddClassWidget.h"

MainView::MainView()
{

}

MainView::MainView(TreeDataPlugin *treeplugin, UserDataPlugin *userplugin, EventDataPlugin *eventplugin)
{
    this->addTab(new ManageStudents(),tr("Students"));
    this->addTab(new AdmAddClassWidget(treeplugin, userplugin), tr("Classes"));
}
