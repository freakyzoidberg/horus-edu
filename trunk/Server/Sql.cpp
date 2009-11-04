#include "Sql.h"
#include "../Common/Logs.h"
#include "../Common/Defines.h"
QMutex Sql::mymute(QMutex::Recursive);
QSemaphore Sql::mtsema;
QHash <QByteArray, bool> Sql::map;

Sql::Sql()
{
    mtsema.acquire();
    mymute.lock();
    for (QHash<QByteArray, bool>::const_iterator it = map.begin(); it != map.end(); it++)
    {
        if (*it)
        {
            if (QSqlDatabase().database(it.key()).isOpen() == false)
            {
                logs::addlog(LOGERROR, "SQL connection have been closed, this should not happen");
            }
            this->append(it.key());
            break;
        }
    }
    map[*this] = false;
    mymute.unlock();
}

Sql::~Sql()
{
    mymute.lock();
    map[*this] = true;
    mtsema.release();
    mymute.unlock();
}

bool Sql::sqlConnect(QString dbName, QString hostname, QString username, QString password, QString driver, int port, int nbConn)
{
    for (int i = 0; i < nbConn; i++)
    {
        QByteArray connm = QVariant(i).toByteArray();
        QSqlDatabase db = QSqlDatabase::addDatabase(driver, connm);

        db.setHostName(hostname);
        db.setDatabaseName(dbName);
        db.setUserName(username);
        db.setPassword(password);
        db.setPort(port);


        //qDebug() << "sql::sqlconnect() connect to" << db.databaseName() << " on " << db.userName() << "@" << db.hostName() << ":" << db.port() << "driver = " << db.driver() << "No:" << connm;
        logs::addlog(LOGINFO,  "Sql connecting to" + db.databaseName() + " infos: " + db.userName() + "@" + db.hostName() + ":" + QVariant(db.port()).toString() + " -- No:" + QString(connm));
        if ( !db.open())
        {
            logs::addlog(LOGERROR, db.lastError().text());
            //qDebug() << "sql::sqlconnect() //hostname : " << hostname << " //dbName : " << dbName << " //username : " << username;
            //qDebug() << "sql::sqlconnect() DriverName = " << db.driver();
            //qDebug() << db.lastError();
            return false;
        }
        map[ connm ] = true;
     }
    mtsema.release(nbConn);
    //qDebug() << map;
    return true;
}
