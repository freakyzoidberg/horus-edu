#include "Sql.h"


QMutex Sql::mymute;
QSemaphore Sql::mtsema(SQLCONNECTIONCOUNT);
bool Sql::con[SQLCONNECTIONCOUNT];

Sql::Sql()
{
    mymute.lock();
    mtsema.acquire(1);
    for (int i = 0; i < SQLCONNECTIONCOUNT; i++)
    {
       if (con[i] == true)
        {
            con[i] = false;
            currentcon = i;
            break;
       }
   }
    mymute.unlock();
}

Sql::~Sql()
{
    if ((currentcon >= 0) && (currentcon < SQLCONNECTIONCOUNT))
    con[currentcon] = true;
    mtsema.release(1);
    //mymute.unlock();
}
bool Sql::sqlconnect(QString dbName, QString hostname, QString username, QString password, QString driver, QString port)
{

bool ok = false;
for (int i = 0; i < SQLCONNECTIONCOUNT; i++)
{
    QString connm = "con";
    connm.append(QVariant(i).toString());
    QSqlDatabase db = QSqlDatabase::addDatabase(driver, connm);

     db.setHostName(hostname);
     db.setDatabaseName(dbName);
     db.setUserName(username);
     db.setPassword(password);
     db.setPort(port.toInt());

    // db.setConnectOptions("CLIENT_INTERACTIVE=1");
     qDebug() << "sql::sqlconnect() connect to" << db.databaseName() << " on " << db.userName() << "@" << db.hostName() << ":" << db.port() << "driver = " << db.driver();
     if (!db.open())
     {
         qDebug() << "sql::sqlconnect() //hostname : " << hostname << " //dbName : " << dbName << " //username : " << username;
         qDebug() << "sql::sqlconnect() DriverName = " << db.driver();
         qDebug() << db.lastError();
         con[i] = false;
         break;
     }
     else
        con[i] = true;
     ok = db.isOpen();
 }
     return (ok);
}


QSqlQuery* Sql::query(QString thequer)
{
    QString connm = "con";
    connm.append(QVariant(currentcon).toString());
    QSqlDatabase localdb = QSqlDatabase::database(connm);

    QSqlQuery* query = new QSqlQuery(thequer, localdb);
    //qDebug() << "used DB = " << connm;

return (query);
}
