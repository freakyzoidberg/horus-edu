#include				"ClientApplication.h"

#include				<QTranslator>
#include				<QSettings>
#include				<QDir>
#include				<QLocale>

#include				"HorusStyle.h"

int						main(int argc, char *argv[])
{
	QTranslator			translator;
    ClientApplication	app(argc, argv);
    QSettings			settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);

	app.setStyle(new HorusStyle());
	translator.load("Horus_" + QLocale::system().name(), settings.value("TranslationsDirectoryPath").toString());
    return (app.exec());
}
