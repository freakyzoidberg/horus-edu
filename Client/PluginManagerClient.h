#ifndef PLUGINMANAGERCLIENT_H
#define PLUGINMANAGERCLIENT_H

#include <QHash>
#include <QList>
#include <QString>
#include <QDir>

#include "../Common/PluginManager.h"

//! To find another plugin with name and/or type
/*! Sample:
 *  PluginManager().findPlugin("NameOfThePlugin")
 *  PluginManager().findPlugin<NetworkPlugin*>()
 *  PluginManager().findPlugin<NetworkPlugin*>("NameOfThePlgin")
 *  PluginManager().findPlugins<NetworkPlugin*>()
 */
class PluginManagerClient : public PluginManager
{
    Q_OBJECT
    Q_INTERFACES(PluginManager)

public:
    void load();
    bool loadPlugin(QString pluginName, QDir path);
    const QHash<QString, Plugin*>& plugins() const;

    static PluginManagerClient* instance();
private:
    PluginManagerClient();
    QHash<QString,Plugin*> _plugins;
};

#endif // PLUGINMANAGERCLIENT_H
