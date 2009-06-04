#ifndef MAINFRAMEWIDGET_H
#define MAINFRAMEWIDGET_H

#include <QFrame>

#include "../ui_MainFrameWidget.h"
#include "MainFrame.h"

class MainFrameWidget : public QFrame
{

public:
    MainFrameWidget(MainFrame *plugin);

private:
    Ui::Frame   ui;
    MainFrame *plugin;

private slots:
    void buttonClicked();
};

#endif // MAINFRAMEWIDGET_H
