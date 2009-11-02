#ifndef PLUGINMANAGERCLIENT_H
#define PLUGINMANAGERCLIENT_H

#include <QHash>
#include <QList>
#include <QString>
#include <QDir>
#include <QEvent>

#include "../Common/PluginManager.h"
#include "../Common/UserData.h"
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
	Q_INTERFACES(PluginManagerCli)

public:
	//PluginManager Interface
	inline const QHash<QString, Plugin*>&	plugins() const { return _plugins; }
	inline UserData*						currentUser() const { return _currentUser; }

public:
	static PluginManagerClient*				instance();
	inline void								setCurrentUser(UserData* _user) { _currentUser = _user; }
	inline bool								isLoaded() { return _loaded; }

public slots:
	void									loadPlugins();

private slots:
	void									sendPluginPacket(const PluginPacket packet);

signals:
	void									sendPacket(const QByteArray packet);
	void									loadProgressChange(int percent);
	void									loaded();

private:
	bool									loadPlugin(QString pluginName, QDir path);

	QHash<QString,Plugin*>					_plugins;
	UserData*								_currentUser;
	bool									_loaded;

	PluginManagerClient() { _currentUser = 0; _loaded = false; }
	~PluginManagerClient() {}
};

#endif // PLUGINMANAGERCLIENT_H
