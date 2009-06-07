#include "Logs.h"
#include "Settings.h"
#include <QtDebug>
//QFile logfile;

logs::logs()
{


}

void logs::addlog(int type, QString msg)
{
    msglogs.append(msg);
}

void logs::setFile(QString filename)
{
    logfile = filename;
}
void logs::run()
 {
    Settings set;
//logfile = new QFile(this);

    QFile *file = new QFile(set.GetSettings("SETTINGS", "SoftFullPath")+"/"+logfile);
    file->open(QFile::WriteOnly);
    QTextStream out(file);
    int i;
    while (42)
    {
    sleep(1);

    if (msglogs.count() > 0)
    {
        for (i = 0;i < msglogs.count(); i++)
        {
            qDebug() << "adding to log : " +  msglogs.at(i);
            out << msglogs.at(i);
        }
        msglogs.clear();
        out.flush();
        file->flush();
    }
    }
//exec();
 }


