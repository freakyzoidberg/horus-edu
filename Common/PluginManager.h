#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QDebug>
#include <QHash>
#include <QList>
#include <QString>

#ifdef HORUS_SERVER
#include <QtSql>
#endif

#include "Plugin.h"
#include "AbstractManager.h"
class UserData;

//! To find another plugin with name and/or type
/*! Sample:
 *  PluginManager().findPlugin("NameOfThePlugin")
 *  PluginManager().findPlugin<NetworkPlugin*>()
 *  PluginManager().findPlugin<NetworkPlugin*>("NameOfThePlugin")
 *  PluginManager().findPlugins<NetworkPlugin*>()
 */
class PluginManager : public AbstractManager
{
  Q_OBJECT
public:
    //! return the plugin with the name in parameter and with a type T
    inline Plugin* findPlugin(const QString& name) const
    {
        return plugins().value( name );
    }
template <typename T>
    inline T findPlugin(const QString& name) const
    {
        return qobject_cast<T>( plugins().value( name ) );
    }
    //! return the first plugin with a type T
template <typename T>
    inline T findPlugin() const
    {
        T qobj;
        foreach (Plugin* plugin, plugins())
            if ((qobj = qobject_cast<T>(plugin)))
                return qobj;
        return 0;
    }
    //! return the list of plugins with a type T
template <typename T>
    inline QList<T> findPlugins() const
    {
        QList<T> list;
        T qobj;
        foreach (Plugin* plugin, plugins())
            if ((qobj = qobject_cast<T>(plugin)))
                list.append(qobj);
        return list;
    }

    virtual const QHash<QString, Plugin*>& plugins() const = 0;
    virtual UserData*                      currentUser() const = 0;

#ifdef HORUS_SERVER
	virtual QSqlQuery					   sqlQuery() = 0;
#endif
};

#ifdef HORUS_SERVER
typedef PluginManager PluginManagerSrv;
Q_DECLARE_INTERFACE(PluginManagerSrv, "net.horus.PluginManagerSrv/1.0");
#endif
#ifdef HORUS_CLIENT
typedef PluginManager PluginManagerCli;
Q_DECLARE_INTERFACE(PluginManagerCli, "net.horus.PluginManagerCli/1.0");
#endif

#endif // PLUGINMANAGER_H
