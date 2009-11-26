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
#ifndef METAPLUGIN_H
#define METAPLUGIN_H

#include <QtCore/qglobal.h>
#include <QObject>
#include <QtPlugin>
#include <QList>

#include "Plugin.h"
#include "PluginManager.h"

class MetaPlugin : public QObject
{
  Q_OBJECT
public:
    QList<Plugin*> pluginList;

    enum PluginsType { HORUS_SERVER_PLUGIN, HORUS_CLIENT_PLUGIN };
    //! automaticaly return the type of this contained Plugins
    inline PluginsType pluginsType() {
#ifdef HORUS_CLIENT
        return HORUS_CLIENT_PLUGIN;
#else
#ifdef HORUS_SERVER
        return HORUS_SERVER_PLUGIN;
#else
  #error "You must define HORUS_CLIENT or HORUS_SERVER in your project."
#endif
#endif
    }
};

Q_DECLARE_INTERFACE(MetaPlugin, "net.horus.MetaPlugin/1.0");

#endif // METAPLUGIN_H
