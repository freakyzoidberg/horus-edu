#include    "PluginManager.h"
#include    <QSettings>
#include    <QDir>
#include    <QString>
#include    <QPluginLoader>
#include    "../Common/Defines.h"

PluginManager::PluginManager(QObject *parent) : QObject::QObject(parent)
{
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
