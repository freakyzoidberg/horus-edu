#include    "PluginManager.h"
#include    <QSettings>
#include    <QDir>
#include    <QString>
#include    <QPluginLoader>
#include    "../Common/Defines.h"
#include    "StartEvent.h"
#include    "StopEvent.h"
#include    <QDebug>
#include    <QApplication>

PluginManager::PluginManager(QObject *parent) : QObject::QObject(parent)
{
}

bool    PluginManager::event(QEvent *event)
{
    qDebug() << "event rteceived";
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

    pluginsDir = QDir(settings.value("Plugins/DirectoryPath", "/Undefined").toString());
    if (pluginsDir.absolutePath() == "/Undefined")
    {
        pluginsDir = QDir(PREFIX);
        if (!pluginsDir.cd(QApplication::organizationName()) || !pluginsDir.cd(QApplication::applicationName()) || !pluginsDir.cd("Plugins"))
        {
            qDebug() << "PluginManager: Error: Plugin path doesn't exist.";
            return ;
        }
    }
    foreach (fileName, pluginsDir.entryList(QDir::Files))
    {
        qDebug() << "test load " << fileName;
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
       // qDebug() << "plugin = " << loader.instance() << "[(0x0) == Failed]";
        QObject *plugin = loader.instance();
        if (plugin)
        {
            qDebug() << "J'ai trouve un plugin !";
            // fumer une clope
        }
        else
            qDebug() << loader.errorString();
        qDebug() << "---------";
     }
}
