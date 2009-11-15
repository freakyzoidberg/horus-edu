#include "MainView.h"

MainView::MainView()
{
    this->addTab(new ManageStudents(),tr("Students"));
}
