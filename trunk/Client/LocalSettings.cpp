/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
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
