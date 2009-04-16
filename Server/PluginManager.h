#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QSettings>
#include <QPluginLoader>
#include <QStringList>
#include <QDebug>

#include "../Common/Defines.h"
#include "IServerPlugin.h"

class PluginManager : public QObject
{
  Q_OBJECT
public:
    static PluginManager* globalInstance();
    IServerPlugin*        getPlugin(const QByteArray&);

private:
    PluginManager();
    static PluginManager* instance;
    QMap<QByteArray,IServerPlugin*> map;

private slots:
    void moduleSendPacket(quint32 userId, const ModulePacket& packet);
};

#endif // PLUGINMANAGER_H
