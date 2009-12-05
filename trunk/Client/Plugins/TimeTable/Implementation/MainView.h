#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>

# include	"../../../../Common/PluginManager.h"

class MainView : public QWidget
{
public:
    MainView(PluginManager *pluginManager);
};

#endif // MAINVIEW_H
