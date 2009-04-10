#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QEvent>

class PluginManager : public QObject
{
public:
    PluginManager(QObject *parent = 0);
    bool event(QEvent *event);

private:
    void    loadPlugins();
};

#endif // PLUGINMANAGER_H
