#ifndef MANAGEEDT_H
#define MANAGEEDT_H

#include <QWidget>
#include <QHBoxLayout>
# include			"../../../../Common/PluginManager.h"
# include			"../../../../Common/UserData.h"

#include "AdmListEdt.h"

class ManageEdt : public QWidget
{
public:
    ManageEdt(QWidget *parent, PluginManager *pluginManager);

private:
    PluginManager	*_pluginManager;
    QHBoxLayout *MainLayout;
    AdmListEdt *_admEDTList;
};

#endif // MANAGEEDT_H
