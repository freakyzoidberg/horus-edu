#include "sql.h"

sql::sql()
{
}

bool sql::sqlconnect(QString dbName, QString hostname, QString username, QString password)
{
    this->db= QSqlDatabase::addDatabase("QPSQL");
     this->db.setHostName(hostname);
     this->db.setDatabaseName(dbName);
     this->db.setUserName(username);
     this->db.setPassword(password);
     bool ok = db.open();
    return (ok);
}
