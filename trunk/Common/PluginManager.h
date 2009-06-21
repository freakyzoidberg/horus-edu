#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QHash>
#include <QList>
#include <QString>
#include "Plugin.h"

//! To find another plugin with name and/or type
/*! Sample:
 *  PluginManager().findPlugin("NameOfThePlgin")
 *  PluginManager().findPlugin<NetworkPlugin*>()
 *  PluginManager().findPlugin<NetworkPlugin*>("NameOfThePlgin")
 *  PluginManager().findPlugins<NetworkPlugin*>()
 */
class PluginManager
{
public:
    //! return the plugin with the name in parameter and with a type T
    inline Plugin* findPlugin(const QString& name) const
    {
        return plugins.value( name );
    }
template <typename T>
    inline T findPlugin(const QString& name) const
    {
        return qobject_cast<T>( plugins.value( name ) );
    }
    //! return the first plugin with a type T
template <typename T>
    inline T findPlugin() const
    {
        T qobj;
        foreach (Plugin* plugin, plugins)
            if ((qobj = qobject_cast<T>(plugin)))
                return qobj;
    }
    //! return the list of plugins with a type T
template <typename T>
    inline QList<T> findPlugins() const
    {
        QList<T> list;
        T qobj;
        foreach (Plugin* plugin, plugins)
            if ((qobj = qobject_cast<T>(plugin)))
                list.append(qobj);
        return list;
    }

    void load();

protected:
    static QHash<QString,Plugin*> plugins;
};

#endif // PLUGINMANAGER_H
