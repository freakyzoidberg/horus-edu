#ifndef SQL_H
#define SQL_H

 #include <QtSql>


class sql
{
public:
    sql();
    bool sqlconnect(QString dbName, QString hostname, QString username, QString password, QString driver, QString port);
private:
     QSqlDatabase db;
};

#endif
