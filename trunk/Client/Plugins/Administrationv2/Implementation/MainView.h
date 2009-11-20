#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QTabWidget>

# include	"../../../../Common/PluginManager.h"

class MainView : public QTabWidget
{
	Q_OBJECT

public:
    MainView(PluginManager *pluginManager);
};

#endif // MAINVIEW_H
