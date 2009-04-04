#ifndef SQL_H
#define SQL_H

 #include <QtSql>
 #include <QString>

class sql
{
public:
    sql();
    void sqlconnect(QString dbName, QString hostname, QString username, QString password);
private:
     QSqlDatabase db;
};

#endif // SQL_H
