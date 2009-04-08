#include "Sql.h"

QMutex Sql::mymute;
Sql::Sql()
{
    mymute.lock();
}

Sql::~Sql()
{
qDebug() << "destructeur";
    mymute.unlock();
}
bool Sql::sqlconnect(QString dbName, QString hostname, QString username, QString password, QString driver, QString port)
{


    this->db= QSqlDatabase::addDatabase(driver);

     this->db.setHostName(hostname);
     this->db.setDatabaseName(dbName);
     this->db.setUserName(username);
     this->db.setPassword(password);
     this->db.setPort(port.toInt());
    // this->db.setConnectOptions("CLIENT_INTERACTIVE=1");
     qDebug() << "sql::sqlconnect() Trying to connect to database " << this->db.databaseName() << " on " << this->db.userName() << "@" << this->db.hostName() << ":" << this->db.port() << " using driver = " << this->db.driver();
     if (!this->db.open())
     {
         qDebug() << "sql::sqlconnect() //hostname : " << hostname << " //dbName : " << dbName << " //username : " << username;
         qDebug() << "sql::sqlconnect() DriverName = " << this->db.driver();
         qDebug() << this->db.lastError();
     }
     bool ok = this->db.isOpen();
     return (ok);
}

QSqlQuery* Sql::Getdb()
{

//    QSqlDatabase localdb = QSqlDatabase::database();
    //qDebug() << "used DB hostname is " << localdb.hostName();


    QSqlQuery* query = new QSqlQuery("SELECT * FROM testdb");
qDebug() << "youpi je vis avant le segfault";
//qDebug() <<query.lastError();
return (query);
}
