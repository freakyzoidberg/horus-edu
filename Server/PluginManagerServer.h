#ifndef PLUGINMANAGERSERVER_H
#define PLUGINMANAGERSERVER_H

#include <QHash>
#include <QList>
#include <QString>

#include "../Common/PluginManager.h"

//! To find another plugin with name and/or type
/*! Sample:
 *  PluginManager().findPlugin("NameOfThePlugin")
 *  PluginManager().findPlugin<NetworkPlugin*>()
 *  PluginManager().findPlugin<NetworkPlugin*>("NameOfThePlgin")
 *  PluginManager().findPlugins<NetworkPlugin*>()
 */
class PluginManagerServer : public PluginManager
{
    Q_OBJECT
    Q_INTERFACES(PluginManager)

public:
    void load();
    const QHash<QString, Plugin*>& plugins() const;

    static PluginManagerServer* instance();
private:
    PluginManagerServer();
    QHash<QString,Plugin*> _plugins;
};

#endif // PLUGINMANAGERSERVER_H
