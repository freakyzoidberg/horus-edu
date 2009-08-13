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
    SettingsDataBasePlugin();
    inline const QString pluginName() const { return "Settings Data Base"; }
    inline const QString pluginVersion() const { return "0.1"; }
    inline const QString getDataType() const { return "Settings"; }
    SettingsData*        getSettings(QString part = QString(), quint8 scope = 0, quint32 userId = 0);

#ifdef HORUS_SERVER
    bool                 verifyDataBase(QSqlQuery&);
#endif

protected:
    //! Return the pointer to the Data with a his unique key read in the stream
    Data*                getDataWithKey(QDataStream& s);

private:
    QList<SettingsData*> settings;
};

#endif // SETTINGSDATABASEPLUGIN_H
