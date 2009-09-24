#include "../Common/Logs.h"
#include "Settings.h"
#include <QtDebug>
#include <QDateTime>
#include "../Common/Defines.h"
#include <QDir>

QMutex *logs::logmutex = new QMutex(QMutex::Recursive);
QList<QString> logs::msglogs;
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
    }
//exec();
 }


