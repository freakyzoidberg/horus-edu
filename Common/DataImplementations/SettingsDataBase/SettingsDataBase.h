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
#ifndef SETTINGSDATABASE_H
#define SETTINGSDATABASE_H

#ifdef HORUS_SERVER
    #include <QtSql>
#endif

#include <QVariant>
#include "../../Defines.h"
#include "../../SettingsData.h"
#include "SettingsDataBasePlugin.h"

class SettingsDataBase : public SettingsData
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerSettingsData)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientSettingsData)
#endif

  friend class SettingsDataBasePlugin;

private:
    SettingsDataBase(SettingsDataBasePlugin* plugin, QString part = QString(), quint8 scope = CLIENT_USER_SCOPE, UserData* user = 0);
	~SettingsDataBase() {}

public:
    //INTERFACE Data
	void				keyToStream(QDataStream& s) const;
	void				dataToStream(QDataStream& s) const;
	void				dataFromStream(QDataStream& s);

	bool				canChange(UserData* user) const;
	bool				canAccess(UserData* user) const;

	const QList<Data*>	dependsOfCreatedData() const;

	QDebug			     operator<<(QDebug debug) const;

    // INTERFACE SettingsData
	inline QVariant		value(const QString& key, QVariant defaultValue = QVariant()) const { if (_values.contains(key)) return _values.value(key); else return defaultValue; }
	void				setValue(const QString& key, const QVariant& val);
	inline QString		part() const { return _part; }
	inline UserData*	owner() const { return _owner; }
	inline quint8		scope() const { return _scope; }

#ifdef HORUS_SERVER
	quint8				serverRead();
	quint8				serverCreate();
	quint8				serverSave();
	quint8				serverRemove();

private:
	bool				_inDatabase;
#endif

private:
	QVariantHash		_values;
	QString				_part;
	UserData*			_owner;
	quint8				_scope;
};

#endif // SETTINGSDATABASE_H
