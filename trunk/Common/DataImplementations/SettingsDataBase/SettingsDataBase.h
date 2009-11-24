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
	bool				inDatabase;
#endif

private:
	QVariantHash		_values;
	QString				_part;
	UserData*			_owner;
	quint8				_scope;
};

#endif // SETTINGSDATABASE_H
