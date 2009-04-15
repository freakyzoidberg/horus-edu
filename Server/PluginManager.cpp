#include    "PluginManager.h"

PluginManager::PluginManager(QObject *parent) : QObject(parent)
{
    loadPlugins();
}

void    PluginManager::loadPlugins()
{
    QSettings s;
    QString path = s.value("PluginsPath", "./plugins").toString();

    s.beginGroup("Plugins");
    foreach (QString key, s.childKeys())
    {
        QString file = path + "/" + s.value(key).toString();
        qDebug() << "PluginManager: Loading" << file;
        QPluginLoader loader(file);
        QObject *plugin = loader.instance();
        if (plugin)
        {
            qDebug() << "PluginManager: plugin loaded";
            // fumer une clope
        }
        else
            qDebug() << "PluginManager: error:" << loader.errorString();
        qDebug() << "---------";
    }

    s.endArray();
    s.endGroup();
}
