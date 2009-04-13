#ifndef SQL_H
#define SQL_H
#include "../Common/Defines.h"
#include <QtSql>
#include <QMutex>
#include <QSemaphore>
#include <QMap>

//!  Sql Class
/*!
  SQL connection and query management for the server
*/
class Sql : public QByteArray
{
public:
    //! Sql constructor
    /*! lock the mutex */
    Sql();
    //! Sql destructor
    /*! unlock the mutex */
    ~Sql();

    //! Connections to the database
    /*!
      \sa sqlconnect()
      \param dbName the database name
      \param hostname the database hostname
      \param username database username
      \param password database password
      \param driver the sql driver used for the connection (eg QMYSQL QPGSQL etc)
      \param port database port
    */
    static bool sqlConnect(QString dbName, QString hostname, QString username, QString password, QString driver, int port, int nbConn);
private:
    //! Mutex for single access to Array of available connection
    static QMutex mymute;
    //! Semaphore for single access socket to database
    static QSemaphore mtsema;
    //! Map of status of SQL connections
    static  QMap<QByteArray, bool> map;
};

#endif

/*





        Sql *Mycon = new Sql();
        QSqlQuery* query = Mycon->query("SELECT * FROM testdb");
        while (query->next()) {
            QString login = query->value(1).toString();
            qDebug() << login;
        }
        delete query;
        delete Mycon;
     */
