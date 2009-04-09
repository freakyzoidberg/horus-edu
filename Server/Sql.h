#ifndef SQL_H
#define SQL_H

 #include <QtSql>
#include <QMutex>

class Sql
{
public:
    Sql();
    ~Sql();
    //private:

    QSqlQuery* query(QString thequer);
    static QMutex mymute;
    bool sqlconnect(QString dbName, QString hostname, QString username, QString password, QString driver, QString port);
};

#endif

/*


     */
