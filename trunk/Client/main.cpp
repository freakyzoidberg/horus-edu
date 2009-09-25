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

	translator.load("Horus_" + settings.value("Locale").toString(), settings.value("TranslationsDirectoryPath").toString());
	app.installTranslator(&translator);
	app.setStyle(new HorusStyle());
    return (app.exec());
}
