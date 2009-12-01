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
#include "SettingsDataBasePlugin.h"
#include "SettingsDataBase.h"

#include "../../PluginManager.h"
#include "../../Plugin.h"
#include "../../UserData.h"
#include "../../UserDataPlugin.h"

SettingsDataBasePlugin::SettingsDataBasePlugin()
{
}

SettingsData* SettingsDataBasePlugin::settings(QString part, quint8 scope, UserData* user)
{
    if IS_SYSTEM_SCOPE(scope)
		user = pluginManager->findPlugin<UserDataPlugin*>()->nobody();
    else if (user == 0)
        user = pluginManager->currentUser();

	foreach (Data* d, _allDatas)
	{
		SettingsDataBase* s = (SettingsDataBase*)d;
		if (s->part() == part && s->scope() == scope && s->owner() == user)
			return s;
	}

	SettingsDataBase* s = new SettingsDataBase(this, part, scope, user);
	s->moveToThread(thread());
	_allDatas.append(s);
	return s;
}

Data* SettingsDataBasePlugin::dataWithKey(QDataStream& s)
{
    QString part;
    quint8 scope;
    quint32 ownerId;
    s >> part >> scope >> ownerId;

	return settings(part, scope, pluginManager->findPlugin<UserDataPlugin*>()->user(ownerId));
}

void SettingsDataBasePlugin::load()
{
#ifdef HORUS_SERVER
	QSqlQuery query = pluginManager->sqlQuery();
	query.prepare("SELECT`user`,`part`,`scope`,`value`,`mtime`FROM`setting`;");

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return;
	}
	UserDataPlugin* userPlugin = pluginManager->findPlugin<UserDataPlugin*>();
	while (query.next())
	{
		SettingsDataBase* s = (SettingsDataBase*)(settings( query.value(1).toString(), //plugin
															query.value(2).toUInt(),	// scope
															userPlugin->user(query.value(0).toUInt()))); //user
		s->_values = query.value(3).toHash();
		s->_lastChange = query.value(4).toDateTime();
		s->_inDatabase = true;
		s->_status = Data::UPTODATE;
	}
#endif
}

void SettingsDataBasePlugin::unload()
{
	foreach (Data* d, _allDatas)
		delete (SettingsDataBase*)d;
	_allDatas.clear();
	DataPlugin::unload();
}

bool SettingsDataBasePlugin::canLoad() const
{
#ifdef HORUS_SERVER
	QSqlQuery query = pluginManager->sqlQuery();
	if ( ! query.exec("CREATE TABLE IF NOT EXISTS`setting`(\
						`user`int(11) NOT NULL,\
						`part`varchar(255) NOT NULL,\
						`scope`int(1) NOT NULL,\
						`value`blob,\
						`mtime`timestamp NOT NULL,\
						KEY`user`(`user`),\
						KEY`part`(`part`),\
						KEY`scope`(`scope`),\
						KEY`mtime`(`mtime`)\
					);")
		||
		 ! query.exec("SELECT`user`,`part`,`scope`,`value`,`mtime`FROM`setting`WHERE`user`=-1;")
		)
	{
		qDebug() << "SettingsDataBasePlugin::canLoad()" << query.lastError();
		return false;
	}
#endif
	return DataPlugin::canLoad();
}
