#include "Settings.h"

#include <QDebug>
#include <QDir>
Settings::Settings()
{
}

void Settings::CheckSettings()
{
    if (GetSettings("Version", "SETTINGS").toInt() != 5)
    {
            qFatal("Server Configuration not found, try running with     --gen-config");
        }
    else
        qDebug() << "Settings::Settings() Config Found in " <<  this->Gsettings.fileName() << "and will use it :)";
}

void Settings::FirstSetSettings()
{
    int found;
    if (this->Gsettings.status() == 0)
    {

        QTextStream streami(stdin);
        QTextStream streamo(stdout);
        QString line;


    this->Gsettings.clear();
    qDebug() << "Settings::FirstSetSettings() Creating config in " <<  this->Gsettings.fileName();
    qDebug() << "Settings::FirstSetSettings() Default Value can be edited";

    this->Gsettings.beginGroup("SQL");
    streamo << "Please specify the folowing :\n";
    streamo << "SQL Driver [ hint : QMYSQL] : ";
    streamo.flush();
    line = streami.readLine();
    //qDebug() << line;
     this->Gsettings.setValue("SQL_DRIVER", (line == "" ? "QMYSQL":line));
     streamo << "SQL HostName [ hint : chine.4--2.net] : ";
    streamo.flush();
    line = streami.readLine();
     this->Gsettings.setValue("SQL_HOSTNAME", (line == "" ? "chine.4--2.net":line));
     streamo << "SQL DB Name [ hint : testhorus] : ";
    streamo.flush();
    line = streami.readLine();
     this->Gsettings.setValue("SQL_DBNAME", (line == "" ? "testhorus":line));
     streamo << "SQL UserName [ hint : horus] : ";
    streamo.flush();
    line = streami.readLine();
     this->Gsettings.setValue("SQL_USERNAME", (line == "" ? "horus":line));
     streamo << "SQL PassWord [ hint : horuspwd] : ";
    streamo.flush();
    line = streami.readLine();
     this->Gsettings.setValue("SQL_PASSWD", (line == "" ? "horuspwd":line));
     streamo << "SQL Port [ hint : 3306] : ";
    streamo.flush();
    line = streami.readLine();
     this->Gsettings.setValue("SQL_PORT", (line == "" ? "3306":line));
    this->Gsettings.endGroup();
    this->Gsettings.beginGroup("SERVER");
    streamo << "Server Port [ hint : 42000] : ";
    streamo.flush();
    line = streami.readLine();
     this->Gsettings.setValue("SRV_PORT", (line == "" ? "42000":line));
    this->Gsettings.endGroup();
    this->Gsettings.beginGroup("SETTINGS");
    this->Gsettings.setValue("Version", "5");
    streamo << "Fullpath to Horus Server diretory[ hint : /opt/Horus/Horus-server/] : ";
    streamo.flush();
    line = streami.readLine();
	this->Gsettings.setValue("PluginsBase", (line == "" ? "/opt/Horus/Horus-server/Plugins/":line+QDir::toNativeSeparators("/Plugins/")));
	this->Gsettings.setValue("SoftFullPath", (line == "" ? "/opt/Horus/Horus-server/":line +QDir::separator()));
    this->Gsettings.endGroup();
    QDir dir(line == "" ? "/opt/Horus/Horus-server/Plugins/":line+QDir::toNativeSeparators("/Plugins/"));
    if (!dir.exists())
     qWarning("Cannot find the plugin directory");
        else
        {
            this->Gsettings.beginGroup("PLUGINS");
            dir.setFilter(QDir::Dirs| QDir::NoDotAndDotDot);
            QFileInfoList list = dir.entryInfoList();
            for (int i = 0; i < list.size(); ++i)
             {
               QFileInfo fileInfo = list.at(i);

                QDir dirfils(fileInfo.absoluteFilePath());
                found = 0;
                if (dirfils.exists())
                    {

                    dirfils.setFilter(QDir::Files| QDir::NoDotAndDotDot);
                    QFileInfoList listfils = dirfils.entryInfoList();
                    for (int j = 0; j < listfils.size(); ++j)
                        {

                        QFileInfo filefilsInfo = listfils.at(j);
                        if ((filefilsInfo.fileName().endsWith(".so") && filefilsInfo.fileName().count(".so") == 1) || (filefilsInfo.fileName().endsWith(".dll") && filefilsInfo.fileName().count(".dll") == 1))
                            {
                                streamo << "Enable plugin "+ fileInfo.fileName() +" [y/N] : ";
                                streamo.flush();
                                line = streami.readLine();
                                if ((line == "y") | (line == "o") | (line == "Y") | (line == "O"))
                                #ifdef Q_OS_WIN
                                this->Gsettings.setValue(fileInfo.fileName(), (fileInfo.fileName()+"/"+filefilsInfo.fileName()));
                                #else
                                this->Gsettings.setValue(fileInfo.fileName(), (fileInfo.fileName()+"/"+filefilsInfo.fileName()));
                                #endif
                             }
                             }
                        }
                    }
            this->Gsettings.endGroup();
        }     
    }
    else
       qDebug() << "Settings::FirstSetSettings() Error writing/reading" <<  this->Gsettings.fileName();
}

QString Settings::GetSettings(QString key, QString group)
{
	return (this->Gsettings.value(group + "/" + key, "").toString());
}