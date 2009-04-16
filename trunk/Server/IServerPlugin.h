#ifndef ISERVERPLUGIN_H
#define ISERVERPLUGIN_H

#include <QObject>
#include <QString>
#include <QtPlugin>

#include "User.h"
#include "../Common/ModulePacket.h"

class IServerPlugin : public QObject
{
  public:
    virtual const QByteArray getName() const = 0;
    virtual const QByteArray getVersion() const = 0;
//    virtual QStringList getPluginsConflicts() const = 0;
//    virtual QStringList getPluginsRequired() const = 0;
//    virtual QStringList getPluginsRecommended() const = 0;
//    virtual QStringList getExports() const = 0;

    virtual void recvPacket(quint32 userId, const ModulePacket&) const = 0;
signals:
    virtual void sendPacket(quint32 userId, const ModulePacket&) const = 0;
};

Q_DECLARE_INTERFACE(IServerPlugin, "net.horus.Server.PluginInterface/1.0");

#endif // ISERVERPLUGIN_H
