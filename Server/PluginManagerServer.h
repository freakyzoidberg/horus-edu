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
public:
    void load();
};

#endif // PLUGINMANAGERSERVER_H
