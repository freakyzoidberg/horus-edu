#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>

class PluginManager : public QObject
{
public:
    PluginManager(QObject *parent = 0);

private:
    void    loadPlugins();
};

#endif // PLUGINMANAGER_H
