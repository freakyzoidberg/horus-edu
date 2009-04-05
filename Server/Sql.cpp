#include "Sql.h"
#define QT_DEBUG_COMPONENT
sql::sql()
{
}

bool sql::sqlconnect(QString dbName, QString hostname, QString username, QString password)
{


    this->db= QSqlDatabase::addDatabase("QMYSQL");

     this->db.setHostName(hostname);
     this->db.setDatabaseName(dbName);
     this->db.setUserName(username);
     this->db.setPassword(password);
     this->db.setPort(3306);
     this->db.setConnectOptions("CLIENT_INTERACTIVE=1");
     qDebug() << "Trying to connect to database " << this->db.databaseName() << " on " << this->db.userName() << "@" << this->db.hostName() << ":" << this->db.port();
     if (!this->db.open())
         qDebug() << "sql::sqlconnect() //hostname : " << hostname << " //dbName : " << dbName << " //username : " << username;
         qDebug() << "sql::sqlconnect() DriverName = " << this->db.driver();
         qDebug() << this->db.lastError();
     bool ok = this->db.isOpen();
     return (ok);
}
