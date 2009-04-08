#include "SqlQuery.h"
#include "Settings.h"
SqlQuery::SqlQuery()
{
}

SqlQuery::SqlQuery( QObject* parent = 0 )
{
}

void SqlQuery::run()
{
    Settings *config = new Settings();

        QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "querythread" );
            db= QSqlDatabase::addDatabase(config->GetSettings("SQL_DRIVER","SQL"));

            db.setHostName( config->GetSettings("SQL_HOSTNAME","SQL"));
            db.setDatabaseName(config->GetSettings("SQL_DBNAME","SQL"));
            db.setUserName(config->GetSettings("SQL_USERNAME","SQL"));
            db.setPassword(config->GetSettings("SQL_PASSWD","SQL"));
            db.setPort(config->GetSettings("SQL_PORT","SQL").toInt());
            // db.setConnectOptions("CLIENT_INTERACTIVE=1");
            qDebug() << "sql::sqlconnect() Trying to connect to database " << db.databaseName() << " on " << db.userName() << "@" << db.hostName() << ":" << db.port() << " using driver = " << db.driver();
            if (!db.open())
            {
                qDebug() << "sql::sqlconnect() //hostname : error"; //<< hostname << " //dbName : " << dbName << " //username : " << username;
            qDebug() << "sql::sqlconnect() DriverName = " << db.driver();
            qDebug() << db.lastError();
            }


            this->exec()
            {
                // wait for work
                // and then execute it...
            }

}
