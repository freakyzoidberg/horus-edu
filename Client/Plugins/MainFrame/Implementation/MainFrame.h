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

    // INTERFACE Plugin
    inline const QString    pluginName() const    { return "MainFrame"; }
    inline const QString    pluginVersion() const { return "0.1"; }
    bool                    canLoad() const;
    void                    load();
    void                    unload();

    // INTERFACE DisplayablePlugin
    inline const QString    getDisplayableName() { return "Main Board"; }
    QWidget*                getWidget();

private slots:
    void                    courseClicked();
private:
    MainFrameWidget*        widget;
};

#endif // MAINFRAME_H
