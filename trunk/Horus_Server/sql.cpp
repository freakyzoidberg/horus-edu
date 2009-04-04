#include "sql.h"

sql::sql()
{
}

void sql::sqlconnect(QString dbName, QString hostname, QString username, QString password)
{
    this->db= QSqlDatabase::addDatabase("QPSQL");
     this->db.setHostName("acidalia");
     this->db.setDatabaseName("customdb");
     this->db.setUserName("mojito");
     this->db.setPassword("J0a1m8");
     bool ok = db.open();

}
