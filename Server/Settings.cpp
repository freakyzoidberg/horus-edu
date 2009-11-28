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
#include "Settings.h"

#include <QDebug>
#include <QDir>

#include "../Common/Defines.h"

Settings::Settings()
{
	this->Gsettings = new QSettings(QSettings::SystemScope, ORGANIZATION_NAME, SERVER_NAME);
}

void Settings::CheckSettings()
{
	if (GetSettings("Version", "SETTINGS").toInt() != 6)
		qFatal("Server Configuration not found, try running with     --gen-config");
	else
		qDebug() << "Settings::Settings() Config Found in " <<  this->Gsettings->fileName() << "and will use it :)";

	if ( ! QFile::exists(GetSettings("SoftFullPath","SETTINGS") + QDir::toNativeSeparators("/ssl/Horus.crt")) ||
		 ! QFile::exists(GetSettings("SoftFullPath","SETTINGS") + QDir::toNativeSeparators("/ssl/Horus.key")))
		qFatal("Ssl certificates not found, please review your config: $SoftFullPath/ssl/Horus[.crt|.key]");
}

void Settings::FirstSetSettings()
{
    int found;
    if (this->Gsettings->status() == 0)
    {

        QTextStream streami(stdin);
        QTextStream streamo(stdout);
        QString line;


    this->Gsettings->clear();
    qDebug() << "Settings::FirstSetSettings() Creating config in " <<  this->Gsettings->fileName();
    qDebug() << "Settings::FirstSetSettings() Default Value can be edited";

    this->Gsettings->beginGroup("SQL");
    streamo << "SQL Settings :\n";
    streamo << "SQL Driver [ hint : QMYSQL] : ";
    streamo.flush();
    line = streami.readLine();
    //qDebug() << line;
     this->Gsettings->setValue("SQL_DRIVER", (line == "" ? "QMYSQL":line));
     streamo << "SQL HostName [ hint : localhost] : ";
    streamo.flush();
    line = streami.readLine();
     this->Gsettings->setValue("SQL_HOSTNAME", (line == "" ? "localhost":line));
     streamo << "SQL DB Name [ hint : testhorus] : ";
    streamo.flush();
    line = streami.readLine();
     this->Gsettings->setValue("SQL_DBNAME", (line == "" ? "testhorus":line));
     streamo << "SQL UserName [ hint : horus] : ";
    streamo.flush();
    line = streami.readLine();
     this->Gsettings->setValue("SQL_USERNAME", (line == "" ? "horus":line));
     streamo << "SQL PassWord [ hint : horuspwd] : ";
    streamo.flush();
    line = streami.readLine();
     this->Gsettings->setValue("SQL_PASSWD", (line == "" ? "horuspwd":line));
     streamo << "SQL Port [ hint : 3306] : ";
    streamo.flush();
    line = streami.readLine();
     this->Gsettings->setValue("SQL_PORT", (line == "" ? "3306":line));
    this->Gsettings->endGroup();
    this->Gsettings->beginGroup("SERVER");
    streamo << "Server Settings :\n";
    streamo << "Server Port [ hint : 42000] : ";
    streamo.flush();
    line = streami.readLine();
     this->Gsettings->setValue("SRV_PORT", (line == "" ? "42000":line));
     streamo << "File Server Port [ hint : 42042] : ";
    streamo.flush();
    line = streami.readLine();
     this->Gsettings->setValue("SRV_FILE_TRANSFERT_PORT", (line == "" ? "42042":line));
    this->Gsettings->endGroup();
    this->Gsettings->beginGroup("SETTINGS");
    this->Gsettings->setValue("Version", "6");
    streamo << "Fullpath to Horus File diretory[ hint : /opt/Horus/Horus-server/Files] : ";
    streamo.flush();
    line = streami.readLine();
        this->Gsettings->setValue("FilesDirectory", (line == "" ? "/opt/Horus/Horus-server/Files/":line+QDir::toNativeSeparators("/Plugins/")));
    streamo << "Fullpath to Horus Server diretory[ hint : /opt/Horus/Horus-server/] : ";
    streamo.flush();
    line = streami.readLine();
	this->Gsettings->setValue("PluginsBase", (line == "" ? "/opt/Horus/Horus-server/Plugins/":line+QDir::toNativeSeparators("/Plugins/")));
	this->Gsettings->setValue("SoftFullPath", (line == "" ? "/opt/Horus/Horus-server/":line +QDir::separator()));
    this->Gsettings->endGroup();
    QDir dir(line == "" ? "/opt/Horus/Horus-server/Plugins/":line+QDir::toNativeSeparators("/Plugins/"));
    if (!dir.exists())
     qWarning("Cannot find the plugin directory");
        else
        {
            this->Gsettings->beginGroup("PLUGINS");
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
                                this->Gsettings->setValue(fileInfo.fileName(), (fileInfo.fileName()+"/"+filefilsInfo.fileName()));
                                #else
                                this->Gsettings->setValue(fileInfo.fileName(), (fileInfo.fileName()+"/"+filefilsInfo.fileName()));
                                #endif
                             }
                             }
                        }
                    }        

            this->Gsettings->endGroup();
        }
    this->Gsettings->beginGroup("MAIL");
    streamo << "Mail Settings :\n";
    streamo << "Mail Hostname [ hint : locahost] : ";
    streamo.flush();
    line = streami.readLine();
    //qDebug() << line;
     this->Gsettings->setValue("MAIL_HOSTNAME", (line == "" ? "localhost":line));
     streamo << "Mail Domain [ hint : horus-edu.net] : ";
    streamo.flush();
    line = streami.readLine();
     this->Gsettings->setValue("MAIL_DOMAIN", (line == "" ? "horus-edu.net":line));
     streamo << "MAIL Server 0:none 1:Courier/Postfix 2:hMailServer [ hint : 0] : ";
    streamo.flush();
    line = streami.readLine();
     this->Gsettings->setValue("MAIL_SERV", (line == "" ? "0":line));
    this->Gsettings->endGroup();
    this->Gsettings->sync();

        if (this->Gsettings->status() != 0)
        {
            qDebug() << "Error while writting conf, check permissions";
        }
    }
    else
       qDebug() << "Settings::FirstSetSettings() Error writing/reading" <<  this->Gsettings->fileName();
}

QString Settings::GetSettings(QString key, QString group)
{
	return (this->Gsettings->value(group + "/" + key, "").toString());
}
