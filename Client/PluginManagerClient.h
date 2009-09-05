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
#include "../Common/PluginPacket.h"

//! To find another plugin with name and/or type
/*! Sample:
 *  pluginManager.findPlugin("NameOfThePlugin")
 *  pluginManager.findPlugin<NetworkPlugin*>()
 *  pluginManager.findPlugin<NetworkPlugin*>("NameOfThePlgin")
 *  pluginManager.findPlugins<NetworkPlugin*>()
 */

class PluginManagerClient : public PluginManager
{
    Q_OBJECT
    Q_INTERFACES(PluginManager)

private:
    inline PluginManagerClient() { user = 0; }
public:
    static PluginManagerClient* instance();
    bool event(QEvent *event);

    inline const QHash<QString, Plugin*>& plugins() const { return _plugins; }

    inline UserData*                      currentUser() const { return user; }
    inline void                           setCurrentUser(UserData* _user) { user = _user; }


private slots:
    void sendPluginPacket(const PluginPacket packet);

signals:
    void sendPacket(const QByteArray packet);

private:
    void loadPlugins();
    bool loadPlugin(QString pluginName, QDir path);

    QHash<QString,Plugin*> _plugins;
    UserData* user;
};

#endif // PLUGINMANAGERCLIENT_H
