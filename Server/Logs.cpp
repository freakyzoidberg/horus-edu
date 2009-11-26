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
#include "../Common/Logs.h"
#include "Settings.h"
#include <QtDebug>
#include <QtGlobal>
#include <QDateTime>
#include "../Common/Defines.h"
#include <QDir>

QMutex *logs::logmutex = new QMutex(QMutex::Recursive);
QList<QString> logs::msglogs;
QString logs::Fatal;
logs::logs()
{


}

void logs::addlog(int type, QString msg)
{
    QString msgtype;
    if (type == LOGERROR)
        msgtype = "ERROR";
    else if (type == LOGWARNING)
        msgtype = "WARNING";
    else if (type == LOGINFO)
        msgtype = "INFO";
    else if (type == LOGDEBUG)
    {
        msgtype = "DEBUG";
        qDebug() << msgtype+"\t"+msg;
    }
    logmutex->lock();
    QDateTime now = QDateTime::currentDateTime();
    logs::msglogs.append(now.toString("d-MMM-yy h:mm:ss")+"\t"+msgtype+"\t"+msg);
    logmutex->unlock();
    if (type == LOGERROR)
    {
        logs::Fatal = now.toString("d-MMM-yy h:mm:ss")+"\t"+msgtype+"\t"+msg;

    }
}

void logs::setFile(QString dir, QString filename)
{
    logfile = filename;
    logdir = dir;
}

void logs::run()
 {
QDir dir(logdir+"/Logs");
 if (!dir.exists())
    dir.mkdir(logdir+"/Logs");
    QFile *file = new QFile(logdir+"/Logs/"+logfile);
    file->open(QFile::Append);
    if (file->isOpen() == false)
       qCritical() << "LOGS Thread : Cannot open -> " + logdir+"/Logs/"+logfile ;
    int i;
    qDebug() << "Saving logs in " + logdir+"/Logs/"+logfile;
    while (42)
    {
    sleep(1);
    if (msglogs.count() > 0)
    {
        logmutex->lock();
        for (i = 0;i < msglogs.count(); i++)
        {
            file->write(QVariant(msglogs.at(i)+"\n").toByteArray());
        }
        msglogs.clear();
        logmutex->unlock();
        file->flush();

    }
    if (Fatal.size() > 0)
        qFatal(QVariant(Fatal).toByteArray());
    }
//exec();
 }


