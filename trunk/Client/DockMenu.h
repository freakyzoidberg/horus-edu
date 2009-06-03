#ifndef DOCKMENU_H
#define DOCKMENU_H

#include <QDockWidget>

#include "ui_DockMenu.h"

#include "PluginManager.h"

class DockMenu : public QDockWidget
{
public:
    DockMenu(QWidget *parent, PluginManager *pluginManager);

private:
    Ui::dock    ui;
};

#endif // DOCKMENU_H
