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
#include	<QApplication>
#include	<QTranslator>

#include	"../Common/Defines.h"
#include	"../Common/LocalSettings.h"
#include	"MainWindow.h"
#include	"LoginDialog.h"
#include	"Notification.h"
#include	"HorusStyle.h"

int						main(int argc, char *argv[])
{
	QApplication		app(argc, argv);
	app.setOrganizationName(ORGANIZATION_NAME);
	app.setOrganizationDomain(ORGANIZATION_DOMAIN);
	app.setApplicationName(CLIENT_NAME);
	app.setApplicationVersion(CLIENT_VERSION);

	qInstallMsgHandler(Notification::notify);

	LocalSettings		settings;
	settings.checkConfig();

	QTranslator			translator;
	translator.load("Horus_" + settings.value("Locale").toString(), settings.value("TranslationsDirectoryPath").toString());

	app.installTranslator(&translator);
	app.setStyle(new HorusStyle());

	LoginDialog login;
	if (login.result() == QDialog::Accepted)
	{
		QMainWindow *window = new MainWindow;
		app.setStyleSheet(window->styleSheet());
		window->setStyleSheet("");
		return (app.exec());
	}

	return 0;
}
