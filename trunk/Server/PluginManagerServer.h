#ifndef PLUGINMANAGERSERVER_H
#define PLUGINMANAGERSERVER_H

#include <QHash>
#include <QList>
#include <QString>

#include "../Common/PluginManager.h"
#include "../Common/UserData.h"

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
    UserData*                      currentUser() const;
    void                           setCurrentUser(UserData* user);

    static PluginManagerServer* instance();
private:
    PluginManagerServer();
    QHash<QString,Plugin*> _plugins;
    QHash<Qt::HANDLE,UserData*> users;
};

#endif // PLUGINMANAGERSERVER_H
