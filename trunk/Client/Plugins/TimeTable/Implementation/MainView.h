#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QTabWidget>

# include	"../../../../Common/PluginManager.h"
#include "EdtWidget.h"
#include "ManageEdt.h"

class MainView : public QTabWidget
{
public:
    MainView(PluginManager *pluginManager);

private:
	 EdtWidget				*EdtSceneView;
	 ManageEdt				*EdtManager;
};

#endif // MAINVIEW_H
