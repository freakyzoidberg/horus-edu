#include    "ClientApplication.h"
#include    <QSettings>
#include    <QDir>
#include    <QString>
#include    <QPluginLoader>
#include    <QtDebug>
#include    "../Common/Defines.h"

ClientApplication::ClientApplication(int argc, char *argv[]) : QApplication(argc, argv)
{
}

ClientApplication::~ClientApplication()
{
    this->unloadPlugins();
    this->stopNetwork();
}

bool    ClientApplication::init()
{
    qDebug() << this->objectName();
    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
    QCoreApplication::setApplicationName(CLIENT_NAME);
    QCoreApplication::setApplicationVersion(CLIENT_VERSION);
    this->loadPlugins();
    this->startNetwork();
    return (true);
}

bool    ClientApplication::loadPlugins()
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
    return (true);
}

bool    ClientApplication::unloadPlugins()
{
    return (true);
}

bool    ClientApplication::reloadPlugins()
{
    this->unloadPlugins();
    return (this->loadPlugins());
}

bool    ClientApplication::startNetwork()
{
    return (true);
}

bool    ClientApplication::stopNetwork()
{
    return (true);
}

bool    ClientApplication::restartNetwork()
{
    this->stopNetwork();
    return (this->startNetwork());
}

