#include "Settings.h"

Settings::Settings()
{
    for (int i = 0; i < QCoreApplication::arguments().count(); i++)
        if (QCoreApplication::arguments().at(i) == "--gen-config")
            {
            FirstSetSettings();
             }
    if (GetSettings("Version", "SETTINGS").toInt() != 3)
    {
            qFatal("Server Configuration not found, try running with     --gen-config");

        }
    else
        qDebug() << "Settings::Settings() Config Found in " <<  this->Gsettings.fileName() << "and will use it :)";
}



void Settings::FirstSetSettings()
{
    if (this->Gsettings.status() == 0)
    {

        QTextStream streami(stdin);
        QTextStream streamo(stdout);
        QString line;



    qDebug() << "Settings::FirstSetSettings() Creating config in " <<  this->Gsettings.fileName();
    qDebug() << "Settings::FirstSetSettings() Default Value can be edited";

    this->Gsettings.beginGroup("SQL");
    streamo << "Please specify the folowing :\n";
    streamo << "SQL Driver [ hint : QMYSQL] : ";
    streamo.flush();
    streami >> line;
     this->Gsettings.setValue("SQL_DRIVER", line);
     streamo << "SQL HostName [ hint : chine.4--2.net] : ";
    streamo.flush();
    streami >> line;
     this->Gsettings.setValue("SQL_HOSTNAME", line);
     streamo << "SQL DB Name [ hint : testhorus] : ";
    streamo.flush();
    streami >> line;
     this->Gsettings.setValue("SQL_DBNAME", line);
     streamo << "SQL UserName [ hint : horus] : ";
    streamo.flush();
    streami >> line;
     this->Gsettings.setValue("SQL_USERNAME", line);
     streamo << "SQL PassWord [ hint : horuspwd] : ";
    streamo.flush();
    streami >> line;
     this->Gsettings.setValue("SQL_PASSWD", line);
     streamo << "SQL Port [ hint : 3306] : ";
    streamo.flush();
    streami >> line;
     this->Gsettings.setValue("SQL_PORT", line);
    this->Gsettings.endGroup();
    this->Gsettings.beginGroup("SERVER");
    streamo << "Server Port [ hint : 42000] : ";
    streamo.flush();
    streami >> line;
     this->Gsettings.setValue("SRV_PORT", line);
    this->Gsettings.endGroup();
    this->Gsettings.beginGroup("SETTINGS");
    this->Gsettings.setValue("Version", "3");
    this->Gsettings.endGroup();
    }
    else
       qDebug() << "Settings::FirstSetSettings() Error writing/reading" <<  this->Gsettings.fileName();
}

QString Settings::GetSettings(QString key, QString group)
{
    QString res;
    this->Gsettings.beginGroup(group);
    if ((res = this->Gsettings.value(key, "").toString()) == "")
            res = "";
    this->Gsettings.endGroup();

    return (res);
}
