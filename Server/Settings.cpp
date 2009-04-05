#include "Settings.h"

Settings::Settings()
{

    if (GetSettings("SRV_PORT", "SERVER") == "")
        {
        FirstSetSettings();
        if (GetSettings("SRV_PORT", "SERVER") == "")
            qDebug() << "Settings::Settings() Definitly an error at getting the configuration";
            else
            qDebug() << "Settings::Settings() Config Found in " <<  this->Gsettings.fileName() << "and will use it :)";
        }
    else
        qDebug() << "Settings::Settings() Config Found in " <<  this->Gsettings.fileName() << "and will use it :)";
}



void Settings::FirstSetSettings()
{
    if (this->Gsettings.status() == 0)
    {
    qDebug() << "Settings::FirstSetSettings() Conf not found Creating it in " <<  this->Gsettings.fileName();
    qDebug() << "Settings::FirstSetSettings() Default Value can be edited";
    this->Gsettings.beginGroup("SQL");
     this->Gsettings.setValue("SQL_DRIVER", "QMYSQL");
     this->Gsettings.setValue("SQL_HOSTNAME", "219.221.96.19");
     this->Gsettings.setValue("SQL_DBNAME", "testhorus");
     this->Gsettings.setValue("SQL_USERNAME", "horus");
     this->Gsettings.setValue("SQL_PASSWD", "horuspwd");
     this->Gsettings.setValue("SQL_PORT", "3306");
    this->Gsettings.endGroup();
    this->Gsettings.beginGroup("SERVER");
     this->Gsettings.setValue("SRV_PORT", "41412");
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
