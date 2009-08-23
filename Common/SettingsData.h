#ifndef SETTINGSDATA_H
#define SETTINGSDATA_H

#include "Data.h"
#include "DataPlugin.h"
#include "SettingsDataPlugin.h"

class UserData;
class SettingsData : public Data
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerData)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientData)
#endif

public:
    inline SettingsData(SettingsDataPlugin* plugin) : Data(plugin) {}
    virtual QVariant  value(const QString& key) const = 0;
    virtual void      setValue(const QString& key, const QVariant& val) = 0;
    virtual QString   part() const = 0;
    virtual UserData* owner() const = 0;
    virtual quint8    scope() const = 0;
};

#ifdef HORUS_SERVER
typedef SettingsData ServerSettingsData;
Q_DECLARE_INTERFACE(ServerSettingsData, "net.horus.ServerSettingsData/1.0");
#endif
#ifdef HORUS_CLIENT
typedef SettingsData ClientSettingsData;
Q_DECLARE_INTERFACE(ClientSettingsData, "net.horus.ClientSettingsData/1.0");
#endif

#endif // SETTINGSDATA_H
