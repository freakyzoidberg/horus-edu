#ifndef PLUGINMANAGERCLIENT_H
#define PLUGINMANAGERCLIENT_H

#include <QHash>
#include <QList>
#include <QString>
#include <QDir>
#include <QEvent>

#include "../Common/PluginManager.h"
#include "../Common/UserData.h"
#include "AbstractManager.h"

//! To find another plugin with name and/or type
/*! Sample:
 *  PluginManager().findPlugin("NameOfThePlugin")
 *  PluginManager().findPlugin<NetworkPlugin*>()
 *  PluginManager().findPlugin<NetworkPlugin*>("NameOfThePlgin")
 *  PluginManager().findPlugins<NetworkPlugin*>()
 */
class PluginManagerClient : public AbstractManager, public PluginManager
{
    Q_OBJECT
    Q_INTERFACES(PluginManager)

public:
    PluginManagerClient();
	bool event(QEvent *event);
    void loadPlugins();
    bool loadPlugin(QString pluginName, QDir path);
    const QHash<QString, Plugin*>& plugins() const;
    UserData*                      currentUser() const;
    void                           setCurrentUser(UserData* user);

private:
    QHash<QString,Plugin*> _plugins;
    UserData* user;
};

#endif // PLUGINMANAGERCLIENT_H
