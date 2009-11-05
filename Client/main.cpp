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
		return (app.exec());
	}

	return 0;
}
