#ifndef MAINFRAMEWIDGET_H
#define MAINFRAMEWIDGET_H

#include <QFrame>
#include <QHash>
#include <QGridLayout>
#include <QLabel>

#include "../ui_MainFrameWidget.h"

#include "MainFrame.h"

class MainFrameWidget : public QFrame
{
    Q_OBJECT
public:
    MainFrameWidget(MainFrame *plugin);

private:
    Ui::Frame   ui;
    MainFrame *plugin;
    QGridLayout *layout;
    QLabel*     connectedAs;
    QLabel*     lastLogin;

public slots:
    void updateInfos();
};

#endif // MAINFRAMEWIDGET_H
