#include "Sql.h"

sql::sql()
{
}

bool sql::sqlconnect(QString dbName, QString hostname, QString username, QString password)
{
    qDebug() << "sql::sqlconnect() start";
    this->db= QSqlDatabase::addDatabase("QMYSQL");
    qDebug() << "sql::sqlconnect() database added";
     this->db.setHostName(hostname);
     this->db.setDatabaseName(dbName);
     this->db.setUserName(username);
     this->db.setPassword(password);
     qDebug() << "sql::sqlconnect() all param set";
     //bool ok = db.open();
     //qDebug() << db.lastError();
     //qDebug() << "sql::sqlconnect() db opened";
    return (0);
}
