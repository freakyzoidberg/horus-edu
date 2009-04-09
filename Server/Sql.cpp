#include "Sql.h"

QMutex Sql::mymute;
Sql::Sql()
{
    mymute.lock();
}

Sql::~Sql()
{
    mymute.unlock();
}
bool Sql::sqlconnect(QString dbName, QString hostname, QString username, QString password, QString driver, QString port)
{
QSqlDatabase db;

    db= QSqlDatabase::addDatabase(driver);

     db.setHostName(hostname);
     db.setDatabaseName(dbName);
     db.setUserName(username);
     db.setPassword(password);
     db.setPort(port.toInt());
    // db.setConnectOptions("CLIENT_INTERACTIVE=1");
     qDebug() << "sql::sqlconnect() Trying to connect to database " << db.databaseName() << " on " << db.userName() << "@" << db.hostName() << ":" << db.port() << " using driver = " << db.driver();
     if (!db.open())
     {
         qDebug() << "sql::sqlconnect() //hostname : " << hostname << " //dbName : " << dbName << " //username : " << username;
         qDebug() << "sql::sqlconnect() DriverName = " << db.driver();
         qDebug() << db.lastError();
     }
     bool ok = db.isOpen();
     return (ok);
}

QSqlQuery* Sql::query(QString thequer)
{

    //QSqlDatabase localdb = QSqlDatabase::database();
    //qDebug() << "used DB hostname is " << localdb.hostName();

    QSqlQuery* query = new QSqlQuery(thequer);


return (query);
}
