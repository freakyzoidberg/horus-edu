#ifndef DOCKMENU_H
#define DOCKMENU_H

#include <QDockWidget>

#include "ui_DockMenu.h"
#include "DisplayablePlugin.h"

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
	static bool	lessThan(DisplayablePlugin *a, DisplayablePlugin *b);
};

#endif // DOCKMENU_H
