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
    inline ~SettingsDataBase() {}

public:
    //INTERFACE Data
    void             keyToStream(QDataStream& s);
    void             dataToStream(QDataStream& s);
    void             dataFromStream(QDataStream& s);

    QDebug           operator<<(QDebug debug) const;

    // INTERFACE SettingsData
    inline QVariant  value(const QString& key) const { return _values.value(key); }
    inline void      setValue(const QString& key, const QVariant& val) { _values[key] = val; }
    inline QString   part() const { return _part; }
    inline UserData* owner() const { return _owner; }
    inline quint8    scope() const { return _scope; }

#ifdef HORUS_SERVER
    void             fillFromDatabase  (QSqlQuery&);
    void             createIntoDatabase(QSqlQuery&);
    void             saveIntoDatabase  (QSqlQuery&);
    void             deleteFromDatabase(QSqlQuery&);
    bool             inDatabase;
#endif

private:
    QVariantHash     _values;
    QString          _part;
    UserData*        _owner;
    quint8           _scope;
};

#endif // SETTINGSDATABASE_H
