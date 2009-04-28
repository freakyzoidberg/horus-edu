#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QSettings>
#include <QPluginLoader>

#include "InterfaceServer.h"
#include "Plugins/IServerPlugin.h"

class PluginManager : public QObject
{
  Q_OBJECT
public:
    static PluginManager* globalInstance();
    IServerPlugin*        getPlugin(const QByteArray&);

private:
    PluginManager();
    static PluginManager* instance;
    //InterfaceServer       serverInterface;
    QMap<QByteArray,IServerPlugin*> map;
};

#endif // PLUGINMANAGER_H
