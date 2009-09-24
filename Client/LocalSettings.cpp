#include "LocalSettings.h"

#include <QSettings>
#include <QDir>
#include <QString>
#include <QDebug>
#include <QCoreApplication>

#include "../Common/Defines.h"

void    LocalSettings::createConfig()
{
    QSettings settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);
    QDir      pluginsDir;
    QString   path;

    if (!settings.contains("Version"))
        settings.setValue("Version", CLIENT_VERSION);
    if (!settings.contains("LessonsDirectoryPath"))
    {
        path = QDir::homePath() + "/.Horus/Lessons";
        if (!pluginsDir.exists(path))
        {
            qDebug() << "ConfigManager: Creating Lessons User Directory." << path;
            if (!pluginsDir.mkpath(path))
                qDebug() << "ConfigManager: Unable to create directory (not the rights ?).";
            else
                settings.setValue("LessonsDirectoryPath", path);
        }
        else
            settings.setValue("LessonsDirectoryPath", path);
    }
    if (!settings.contains("TranslationsDirectoryPath"))
    {
        path = QDir::homePath() + "/.Horus/Translations";
        if (!pluginsDir.exists(path))
        {
            qDebug() << "ConfigManager: Creating Translations User Directory." << path;
            if (!pluginsDir.mkpath(path))
                qDebug() << "ConfigManager: Unable to create directory (not the rights ?).";
            else
                settings.setValue("TranslationsDirectoryPath", path);
        }
        else
            settings.setValue("LessonsDirectoryPath", path);
    }
    if (!settings.contains("Plugins/UserDirectoryPath"))
    {
        path = QDir::homePath() + "/.Horus/Plugins";
        if (!pluginsDir.exists(path))
        {
            qDebug() << "ConfigManager: Creating Plugins User Directory." << path;
            if (!pluginsDir.mkpath(path))
                qDebug() << "ConfigManager: Unable to create directory (not the rights ?).";
            else
                settings.setValue("Plugins/UserDirectoryPath", path);
        }
        else
            settings.setValue("Plugins/UserDirectoryPath", path);
    }
    if (!settings.contains("Plugins/SystemDirectoryPath"))
    {
        path = PREFIX + QCoreApplication::organizationName() + "/" + QCoreApplication::applicationName() + "/Plugins";
        if (!pluginsDir.exists(path))
        {
            qDebug() << "ConfigManager: Creating Plugins System Directory." << path;
            if (!pluginsDir.mkpath(path))
                qDebug() << "ConfigManager: Unable to create directory (not the rights ?).";
            else
                settings.setValue("Plugins/SystemDirectoryPath", path);
        }
        else
            settings.setValue("Plugins/SystemDirectoryPath", path);
    }
    if (!settings.contains("Network/Server"))
        settings.setValue("Network/Server", "localhost");
    if (!settings.contains("Network/Port"))
        settings.setValue("Network/Port", 42000);
    if (!settings.contains("Network/PortTransfert"))
        settings.setValue("Network/PortTransfert", 42042);
    settings.sync();
}
