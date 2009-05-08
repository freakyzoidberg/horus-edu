#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QThread>
#include <QEvent>
#include <QString>
#include <QMap>
#include <QDir>
#include "IClientPlugin.h"
#include "ClientApplication.h"

class PluginManager : public QThread
{
    Q_OBJECT

public:
    PluginManager(ClientApplication *parent = 0);
    bool    event(QEvent *event);

protected:
    void    run();

private:
    void    loadPlugins();
    bool    loadPlugin(QString pluginName, QDir path);
    QObject *findPlugin(QString &) const;

private:
    QMap<QString, IClientPlugin *>    pluginsList;
    ClientApplication *parent;
};

#endif // PLUGINMANAGER_H
