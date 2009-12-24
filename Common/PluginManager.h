/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
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
class UserData;
class TreeData;

//! To find another plugin with name and/or type
/*! Sample:
 *  PluginManager().findPlugin("NameOfThePlugin")
 *  PluginManager().findPlugin<NetworkPlugin*>()
 *  PluginManager().findPlugin<NetworkPlugin*>("NameOfThePlugin")
 *  PluginManager().findPlugins<NetworkPlugin*>()
 */
class PluginManager : public QObject
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
	virtual UserData*					   nobody() const = 0;
	virtual TreeData*					   rootNode() const = 0;

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
