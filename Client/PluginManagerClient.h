#ifndef PLUGINMANAGERCLIENT_H
#define PLUGINMANAGERCLIENT_H

#include <QHash>
#include <QList>
#include <QString>
#include <QDir>
#include <QEvent>

#include "../Common/PluginManager.h"
#include "../Common/UserData.h"
#include "../Common/AbstractManager.h"

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
    inline PluginManagerClient() { user = 0; }
    bool event(QEvent *event);

    inline const QHash<QString, Plugin*>& plugins() const { return _plugins; }

    inline UserData*                      currentUser() const { return user; }
    inline void                           setCurrentUser(UserData* _user) { user = _user; }




private:
    void loadPlugins();
    bool loadPlugin(QString pluginName, QDir path);

    QHash<QString,Plugin*> _plugins;
    UserData* user;
};

#endif // PLUGINMANAGERCLIENT_H
