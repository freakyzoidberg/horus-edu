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
#include "UserSettings.h"
#include "Sql.h"

//UserSettings::UserSettings(quint32 _userId, const QByteArray& _plugin, CommSettings::Scope _scope)
//{
//    if (_scope == CommSettings::CLIENT_USER_SCOPE ||
//        _scope == CommSettings::SERVER_USER_SCOPE)
//        userId = _userId;
//    else
//        userId = 0;
//
//    plugin = _plugin;
//    scope = _scope;
//    exist = false;
//    readDatabase();
//}
//
//void UserSettings::readDatabase()
//{
//    Sql con;
//    QSqlQuery query(QSqlDatabase::database(con));
//
//    query.prepare("SELECT value FROM settings WHERE user=? AND plugin=? AND scope=?;");
//    query.addBindValue(userId);
//    query.addBindValue(plugin.length() ? plugin : "");
//    query.addBindValue(scope);
//
//    if ( ! query.exec())
//    {
//        qDebug() << query.lastError();
//        return;
//    }
//
//    if (query.next())
//    {
//        settings = query.value(0).toByteArray();
//        exist = true;
//    }
//}
//
//void UserSettings::set(const QByteArray& _settings)
//{
//    Sql con;
//    QSqlQuery query(QSqlDatabase::database(con));
//
//    if ( ! exist)
//        query.prepare("INSERT INTO settings (value,user,plugin,scope) VALUES (?,?,?,?);");
//    else if (settings != _settings)
//        query.prepare("UPDATE settings SET value=? WHERE user=? AND plugin=? AND scope=?;");
//    else
//        return;//Up to date
//
//    query.addBindValue(_settings, QSql::Binary);
//    query.addBindValue(userId);
//    query.addBindValue(plugin.length() ? plugin : "");
//    query.addBindValue(scope);
//
//    if ( ! query.exec())
//    {
//        qDebug() << query.lastError();
//        return;
//    }
//
//    settings = _settings;
//}
//
//const QByteArray& UserSettings::get()
//{
//    return settings;
//}
