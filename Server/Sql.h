#ifndef SQL_H
#define SQL_H

 #include <QtSql>


class sql
{
public:
    sql();
    bool sqlconnect(QString dbName, QString hostname, QString username, QString password, QString driver, QString port);
    //private:
    QSqlDatabase db;

};

#endif

/*

    QSqlDatabase db = QSqlDatabase::database();
    qDebug() << "used DB hostname is " << db.hostName();

    QSqlQuery query("SELECT * FROM testdb");
     while (query.next()) {
         QString login = query.value(1).toString();
         qDebug() << login;
     }
     */
