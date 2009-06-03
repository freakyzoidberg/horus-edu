#ifndef DOCKMENU_H
#define DOCKMENU_H

#include <QDockWidget>

#include "ui_DockMenu.h"

class DockMenu : public QDockWidget
{
public:
    DockMenu(QWidget *parent);

private:
    Ui::dock    ui;
};

#endif // DOCKMENU_H
