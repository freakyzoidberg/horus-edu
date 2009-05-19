#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>

#include "InterfaceServer.h"
#include "Plugins/IServerPlugin.h"

//! Load an store the Server Plugins
class PluginManager : public QObject
{
  Q_OBJECT
public:
    //! return the global instance of this object
    static PluginManager* globalInstance();
    //! return the plugin with the name in parameter
    IServerPlugin*        getPlugin(const QByteArray&) const;

private:
    //! private construct: not possible to have multiple instance
    PluginManager();
    //! singleton
    static PluginManager* instance;
    //! HashTable containing every loaded Plugins
    QHash<QByteArray,IServerPlugin*> map;
};

#endif // PLUGINMANAGER_H
