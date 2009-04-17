#ifndef ISERVERPLUGIN_H
#define ISERVERPLUGIN_H

#include <QObject>
#include <QString>
#include <QtPlugin>

#include "../../Common/ModulePacket.h"
#include "IServer.h"

class IServer;

class IServerPlugin : public QObject
{
  public:
    IServer* server;
    virtual const QByteArray name() const = 0;
    virtual const QByteArray version() const = 0;
//    virtual QStringList getPluginsConflicts() const = 0;
//    virtual QStringList getPluginsRequired() const = 0;
//    virtual QStringList getPluginsRecommended() const = 0;
//    virtual QStringList getExports() const = 0;

    virtual void recvPacket(quint32 userId, const ModulePacket&) const = 0;
};

Q_DECLARE_INTERFACE(IServerPlugin, "net.horus.Server.PluginInterface/1.0");

#endif // ISERVERPLUGIN_H
