#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QtPlugin>
#include <QHash>

#include "../../../DisplayablePlugin.h"

class MainFrameWidget;

class MainFrame : public DisplayablePlugin
{
    Q_OBJECT
    Q_INTERFACES(Plugin DisplayablePlugin)

public:
    MainFrame();
    const QByteArray    getName() const;
    const QByteArray    getVersion() const;
    bool                event(QEvent *event);
    QWidget             *getWidget();

private:
    MainFrameWidget     *widget;
};

#endif // MAINFRAME_H
