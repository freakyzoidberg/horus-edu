#include "../Common/LocalSettings.h"

#include <QDir>
#include <QString>
#include <QDebug>
#include <QLocale>
#include <QApplication>

#include "../Common/Defines.h"


LocalSettings::LocalSettings() :
		QSettings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat)
{}

void    LocalSettings::checkConfig()
{
    QDir      pluginsDir;
    QString   path;

	if ( ! contains("Version"))
		setValue("Version", CLIENT_VERSION);
	if ( ! contains("LessonsDirectoryPath"))
    {
        path = QDir::homePath() + "/.Horus/Lessons";
		if ( ! pluginsDir.exists(path))
        {
            qDebug() << tr("ConfigManager: Creating Lessons User Directory.") << path;
			if ( ! pluginsDir.mkpath(path))
                qWarning() << tr("ConfigManager: Unable to create directory (not the rights ?).");
            else
				setValue("LessonsDirectoryPath", path);
        }
        else
			setValue("LessonsDirectoryPath", path);
    }
	if ( ! contains("TranslationsDirectoryPath"))
    {
        path = QDir::homePath() + "/.Horus/Translations";
		if ( ! pluginsDir.exists(path))
        {
            qDebug() << tr("ConfigManager: Creating Translations User Directory.") << path;
			if ( ! pluginsDir.mkpath(path))
                qWarning() << tr("ConfigManager: Unable to create directory (not the rights ?).");
            else
				setValue("TranslationsDirectoryPath", path);
        }
        else
			setValue("LessonsDirectoryPath", path);
    }
	if ( ! contains("Locale"))
		setValue("Locale", QLocale::system().name());
	if ( ! contains("Plugins/UserDirectoryPath"))
    {
        path = QDir::homePath() + "/.Horus/Plugins";
		if ( ! pluginsDir.exists(path))
        {
            qDebug() << tr("ConfigManager: Creating Plugins User Directory.") << path;
			if ( ! pluginsDir.mkpath(path))
                qWarning() << tr("ConfigManager: Unable to create directory (not the rights ?).");
            else
				setValue("Plugins/UserDirectoryPath", path);
        }
        else
			setValue("Plugins/UserDirectoryPath", path);
    }
	if ( ! contains("Plugins/SystemDirectoryPath"))
    {
		path = PREFIX + QApplication::organizationName() + "/" + QApplication::applicationName() + "/Plugins";
		if ( ! pluginsDir.exists(path))
        {
            qDebug() << tr("ConfigManager: Creating Plugins System Directory.") << path;
			if ( ! pluginsDir.mkpath(path))
                qWarning() << tr("ConfigManager: Unable to create directory (not the rights ?).");
            else
				setValue("Plugins/SystemDirectoryPath", path);
        }
        else
			setValue("Plugins/SystemDirectoryPath", path);
    }
	if ( ! contains("Network/Server"))
		setValue("Network/Server", "localhost");
	if ( ! contains("Network/Port"))
		setValue("Network/Port", 42000);
	if ( ! contains("Network/PortTransfert"))
		setValue("Network/PortTransfert", 42042);
	sync();
}
