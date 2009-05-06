#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QEvent>
#include <QString>
#include <QMap>
#include <QDir>
#include "IClientPlugin.h"

class PluginManager : public QObject
{
    Q_OBJECT

public:
    PluginManager(QObject *parent = 0);
    bool event(QEvent *event);

private:
    void    loadPlugins();
    bool    loadPlugin(QString pluginName, QDir path);
    QObject *findPlugin(QString &) const;

private:
    QMap<QString, IClientPlugin *>    pluginsList;
};

#endif // PLUGINMANAGER_H
