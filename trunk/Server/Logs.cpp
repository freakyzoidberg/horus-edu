#include "Logs.h"
#include "Settings.h"
#include <QtDebug>
#include <QDateTime>
#include "../Common/Defines.h"
//QFile logfile;
QMutex *logs::logmutex = new QMutex(QMutex::Recursive);
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
    msglogs.append(now.toString("d-MMM-yy h:mm:ss")+"\t"+msgtype+"\t"+msg);
    logmutex->unlock();
}

void logs::setFile(QString filename)
{
    logfile = filename;
}

void logs::run()
 {
    QFile *file = new QFile(logfile);
    file->open(QFile::Append);
    if (file->isOpen() == false)
       qCritical() << "LOGS Thread : Cannot open -> " + logfile ;
    int i;
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


