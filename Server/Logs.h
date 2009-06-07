#ifndef LOGS_H
#define LOGS_H
 #include <QFile>
#include <QThread>

class logs : public QThread
{
     Q_OBJECT
public:
    logs();
    void addlog(int type, QString msg);
    void setFile(QString filename);
    void run();

private:
   QString logfile;
   QList<QString> msglogs;
};

#endif // LOGS_H
