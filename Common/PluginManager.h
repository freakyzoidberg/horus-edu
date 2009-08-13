#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QDebug>
#include <QHash>
#include <QList>
#include <QString>

#include "Plugin.h"
#include "UserData.h"

//! To find another plugin with name and/or type
/*! Sample:
 *  PluginManager().findPlugin("NameOfThePlugin")
 *  PluginManager().findPlugin<NetworkPlugin*>()
 *  PluginManager().findPlugin<NetworkPlugin*>("NameOfThePlugin")
 *  PluginManager().findPlugins<NetworkPlugin*>()
 */
class PluginManager : virtual public QObject
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
};

Q_DECLARE_INTERFACE(PluginManager, "net.horus.PluginManager/1.0");

#endif // PLUGINMANAGER_H
