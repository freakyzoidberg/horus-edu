#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "MainFrame_global.h"

#include <QtPlugin>

#include "../../../IClientPlugin.h"
#include "../../../IDisplayablePlugin.h"

class MAINFRAMESHARED_EXPORT MainFrame : public IClientPlugin, public IDisplayablePlugin
{
    Q_OBJECT
    Q_INTERFACES(IClientPlugin)
    Q_INTERFACES(IDisplayablePlugin)

public:
    MainFrame();
    IClient             *client;
    IDisplayable             *display;
    const QByteArray    getName() const;
    const QByteArray    getVersion() const;
    QStringList         getPluginsConflicts() const;
    QStringList         getPluginsRequired() const;
    QStringList         getPluginsRecommended() const;
    bool                event(QEvent *event);
    QWidget             *getWidget();
};

#endif // MAINFRAME_H
