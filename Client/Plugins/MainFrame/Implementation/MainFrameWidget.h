#ifndef MAINFRAMEWIDGET_H
#define MAINFRAMEWIDGET_H

#include <QFrame>

#include "../ui_MainFrameWidget.h"

class MainFrameWidget : public QFrame
{
public:
    MainFrameWidget();

private:
    Ui::Frame   ui;
};

#endif // MAINFRAMEWIDGET_H
