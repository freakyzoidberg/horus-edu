#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QTabWidget>

# include	"../../../../Common/PluginManager.h"

class MainView : public QTabWidget
{
public:
    MainView(PluginManager *pluginManager);
};

#endif // MAINVIEW_H
