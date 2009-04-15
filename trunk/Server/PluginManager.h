#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QSettings>
//#include <QDir>
#include <QPluginLoader>
#include <QDebug>
#include <QStringList>

#include "../Common/Defines.h"

class PluginManager : public QObject
{
    Q_OBJECT

public:
    PluginManager(QObject *parent = 0);

private:
    void    loadPlugins();
};

#endif // PLUGINMANAGER_H
