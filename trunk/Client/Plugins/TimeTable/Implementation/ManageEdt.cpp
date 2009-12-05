#include "ManageEdt.h"
#include <QHBoxLayout>
ManageEdt::ManageEdt(QWidget *parent, PluginManager *pluginManager) : QWidget(parent), _pluginManager(pluginManager)
{
    MainLayout = new QHBoxLayout();
    MainLayout->setSpacing(0);
    MainLayout->setMargin(2);

    _admEDTList = new AdmListEdt(pluginManager);

}
