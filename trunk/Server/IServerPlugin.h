#ifndef ISERVERPLUGIN_H
#define ISERVERPLUGIN_H

#include <QEvent>

class IServerPlugin
{
  public:
    virtual QString     getName() const = 0;
    virtual QString     getVersion() const = 0;
    virtual QStringList getPluginsConflicts() const = 0;
    virtual QStringList getPluginsRequired() const = 0;
    virtual QStringList getPluginsRecommended() const = 0;
    virtual QStringList getExports() const = 0;

signals:
    virtual void        sendPacket(quint32 user, QByteArray ) const = 0;
};

Q_DECLARE_INTERFACE(IServerPlugin, "net.horus.Server.PluginInterface/1.0");

#endif // ISERVERPLUGIN_H
