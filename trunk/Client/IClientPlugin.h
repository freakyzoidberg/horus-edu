#ifndef ICLIENTPLUGIN_H
#define ICLIENTPLUGIN_H

#include <QObject>
#include <QEvent>

class IClient;

class IClientPlugin : public QObject
{
  public:
    IClient                     *client;
    virtual const QByteArray    getName() const = 0;
    virtual const QByteArray    getVersion() const = 0;
    virtual QStringList         getPluginsConflicts() const = 0;
    virtual QStringList         getPluginsRequired() const = 0;
    virtual QStringList         getPluginsRecommended() const = 0;
//    virtual QStringList         getExports() const = 0;
    virtual bool                event(QEvent *) = 0;
};

Q_DECLARE_INTERFACE(IClientPlugin, "net.horus.Client.PluginInterface/1.0");

#endif // ICLIENTPLUGIN_H
