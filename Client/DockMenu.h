#ifndef DOCKMENU_H
#define DOCKMENU_H

#include <QDockWidget>

#include "ui_DockMenu.h"

#include "PluginManager.h"

class DockMenu : public QDockWidget
{
    Q_OBJECT

public:
    DockMenu(QWidget *parent, PluginManager *pluginManager);

public slots:
    void itemClicked();

private:
    Ui::dock    ui;
    PluginManager *pluginManager;
};

#endif // DOCKMENU_H
