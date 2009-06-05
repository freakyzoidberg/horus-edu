#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "MainFrame_global.h"

#include <QtPlugin>
#include <QHash>

#include "../../../IClientPlugin.h"
#include "../../../IDisplayablePlugin.h"
#include "../../../INetworkPlugin.h"

class MainFrameWidget;

class MAINFRAMESHARED_EXPORT MainFrame : public IClientPlugin, public IDisplayablePlugin, public INetworkPlugin
{
    Q_OBJECT
    Q_INTERFACES(IClientPlugin)
    Q_INTERFACES(IDisplayablePlugin)
    Q_INTERFACES(INetworkPlugin)

public:
    MainFrame();
    const QByteArray    getName() const;
    const QByteArray    getVersion() const;
    QStringList         getPluginsConflicts() const;
    QStringList         getPluginsRequired() const;
    QStringList         getPluginsRecommended() const;
    bool                event(QEvent *event);
    QWidget             *getWidget();
    void                recvPacket(const PluginPacket &packet);

private:
    MainFrameWidget     *widget;
    QHash<QString, QVariant>      userInfo;

signals:
    void infoUpdated(QHash<QString, QVariant> userInfo);
};

#endif // MAINFRAME_H
