#include    "PluginManager.h"
#include    <QSettings>
#include    <QDir>
#include    <QString>
#include    <QPluginLoader>
#include    "../Common/Defines.h"
#include    "StartEvent.h"
#include    "StopEvent.h"
#include    <QDebug>

PluginManager::PluginManager(QObject *parent) : QObject::QObject(parent)
{
}

bool    PluginManager::event(QEvent *event)
{
    if (event->type() == StartEvent::type)
    {
        qDebug() << "PluginManager: Receive StartEvent";
        this->loadPlugins();
        return (true);
    }
    else if (event->type() == StopEvent::type)
    {
        qDebug() << "PluginManager: Receive StopEvent";
        return (true);
    }
    else
        return (false);
}

void    PluginManager::loadPlugins()
{
    QSettings   settings;
    QDir        pluginsDir;
    QString     fileName;

    pluginsDir = QDir(settings.value("Plugins/DirectoryPath", QString(DEFAULT_PLUGINS_DIRECTORY_PATH)).toString());
    foreach (fileName, pluginsDir.entryList(QDir::Files)) {
         QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
         QObject *plugin = loader.instance();
         if (plugin)
         {
             // fumer une clope
         }
     }
}
