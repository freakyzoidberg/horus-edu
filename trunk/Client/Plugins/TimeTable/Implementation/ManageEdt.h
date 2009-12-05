#ifndef MANAGEEDT_H
#define MANAGEEDT_H

#include <QWidget>
# include			"../../../../Common/PluginManager.h"
# include			"../../../../Common/UserData.h"

class ManageEdt : public QWidget
{
public:
    ManageEdt(QWidget *parent, PluginManager *pluginManager);

private:
    PluginManager	*_pluginManager;
};

#endif // MANAGEEDT_H
