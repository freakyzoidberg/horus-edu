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
#ifndef SETTINGSDATABASEPLUGIN_H
#define SETTINGSDATABASEPLUGIN_H

#include <QHash>
#include "../../SettingsDataPlugin.h"

class Data;
class SettingsData;
class SettingsDataBase;
class SettingsDataBasePlugin : public SettingsDataPlugin
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerSettingsDataPlugin)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientSettingsDataPlugin)
#endif

public:
	SettingsData*			settings(QString part = QString(), quint8 scope = CLIENT_USER_SCOPE, UserData* user = 0);
	SettingsDataBasePlugin();


	//Plugin
public:
	inline const QString	pluginName() const { return "Settings Data Base"; }
	inline const QString	pluginVersion() const { return "0.1"; }
	void					load();
	void					unload();
	bool					canLoad() const;


	//DataPlugin
protected:
    //! Return the pointer to the Data with a his unique key read in the stream
	Data*					dataWithKey(QDataStream& s);
};

#endif // SETTINGSDATABASEPLUGIN_H
