#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QtPlugin>
#include <QHash>

#include "../../../DisplayablePlugin.h"

class MainFrameWidget;

class MainFrame : public DisplayablePlugin
{
    Q_OBJECT
    Q_INTERFACES(DisplayablePlugin)

public:
    MainFrame();
    inline const QString pluginName() const { return "MainFrame"; }
    inline const QString pluginVersion() const { return "0.1"; }
    bool                 event(QEvent *event);
    QWidget*             getWidget();

private:
    MainFrameWidget*     widget;

public slots:
    void courseClicked();
};

#endif // MAINFRAME_H
