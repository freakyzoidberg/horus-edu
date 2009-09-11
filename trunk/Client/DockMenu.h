#ifndef DOCKMENU_H
#define DOCKMENU_H

#include <QDockWidget>

#include "ui_DockMenu.h"

class MainWindow;
class DockMenu : public QDockWidget
{
    Q_OBJECT

public:
    DockMenu(MainWindow* parent);

public slots:
    void itemClicked();

private:
    Ui::dock    ui;
};

#endif // DOCKMENU_H
