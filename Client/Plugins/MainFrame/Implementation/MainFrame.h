#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "MainFrame_global.h"

#include "../../../IClientPlugin.h"

class MAINFRAMESHARED_EXPORT MainFrame : public IClientPlugin
{
    Q_OBJECT
    Q_INTERFACES(IClientPlugin)

public:
    MainFrame();
    IClient             *client;
    const QByteArray    getName() const;
    const QByteArray    getVersion() const;
    QStringList         getPluginsConflicts() const;
    QStringList         getPluginsRequired() const;
    QStringList         getPluginsRecommended() const;
    bool                event(QEvent *event);
};

#endif // MAINFRAME_H
