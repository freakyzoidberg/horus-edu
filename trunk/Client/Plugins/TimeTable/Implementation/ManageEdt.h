#ifndef MANAGEEDT_H
#define MANAGEEDT_H

#include <QWidget>
#include <QHBoxLayout>
#include <QFrame>
# include			"../../../../Common/PluginManager.h"
# include			"../../../../Common/UserData.h"

#include "AdmListEdt.h"

class ManageEdt : public QWidget
{
public:
	ManageEdt(PluginManager *pluginManager);

private:
    PluginManager	*_pluginManager;
	QHBoxLayout		*MainLayout;
	AdmListEdt		*_admEDTList;
	QFrame			*informationsFrame;
	QVBoxLayout		*informationsLayout;

};

#endif // MANAGEEDT_H
