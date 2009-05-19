#include "Sql.h"

QMutex Sql::mymute;
QSemaphore Sql::mtsema;
QHash <QByteArray, bool> Sql::map;

Sql::Sql() : QByteArray("")
{
    mtsema.acquire();
    mymute.lock();
    for (QHash<QByteArray, bool>::const_iterator it = map.begin(); it != map.end(); it++)
    {
        if (*it)
        {
            this->append(it.key());
            break;
        }
    }
    map[*this] = false;
    mymute.unlock();
    qDebug() << "Using Sql connexion" << *this;
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

        qDebug() << "sql::sqlconnect() connect to" << db.databaseName() << " on " << db.userName() << "@" << db.hostName() << ":" << db.port() << "driver = " << db.driver() << "No:" << connm;
        if ( ! db.open())
        {
            qDebug() << "sql::sqlconnect() //hostname : " << hostname << " //dbName : " << dbName << " //username : " << username;
            qDebug() << "sql::sqlconnect() DriverName = " << db.driver();
            qDebug() << db.lastError();
            return false;
        }

        map[ connm ] = true;
     }
    mtsema.release(nbConn);
    qDebug() << map;
    return true;
}
