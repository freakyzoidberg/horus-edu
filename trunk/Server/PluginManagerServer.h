#ifndef PLUGINMANAGERSERVER_H
#define PLUGINMANAGERSERVER_H

#include <QHash>
#include <QList>
#include <QString>

#include "../Common/PluginManager.h"
#include "../Common/UserData.h"
#include "../Common/PluginPacket.h"
#include "Sql.h"

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
	Q_INTERFACES(PluginManagerSrv)

public:
    void load();
    const QHash<QString, Plugin*>& plugins() const;
    UserData*                      currentUser() const;
    void                           setCurrentUser(UserData* user);
	QSqlQuery					   sqlQuery();

    static PluginManagerServer* instance();

private slots:
    void sendPluginPacket(UserData* user, const PluginPacket packet);

private:
    PluginManagerServer();
	QHash<QString,Plugin*>		_plugins;
	QHash<Qt::HANDLE,UserData*> _users;
	QHash<Qt::HANDLE,Sql*>		_sqlConnexions;
};

#endif // PLUGINMANAGERSERVER_H
