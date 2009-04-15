#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QEvent>
#include <QString>
#include <QMap>

class PluginManager : public QObject
{
    Q_OBJECT

public:
    PluginManager(QObject *parent = 0);
    bool event(QEvent *event);

private:
    void    loadPlugins();
    QObject *findPlugin(QString &) const;

private:
    QMap<QString, QObject *>    pluginsList;
};

#endif // PLUGINMANAGER_H
