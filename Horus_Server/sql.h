#ifndef SQL_H
#define SQL_H

 #include <QtSql>
 #include <QString>

class sql
{
public:
    sql();
    bool sqlconnect(QString dbName, QString hostname, QString username, QString password);
private:
     QSqlDatabase db;
};

#endif
