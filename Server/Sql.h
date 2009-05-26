#ifndef SQL_H
#define SQL_H
#include <QtSql>
#include <QByteArray>
#include <QMutex>
#include <QSemaphore>
#include <QHash>

#include "Plugins/IServer.h"

//!  Manage pool of sql connection
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
      \param dbName the database name
      \param hostname the database hostname
      \param username database username
      \param password database password
      \param driver the sql driver used for the connection (eg QMYSQL QPGSQL etc)
      \param port database port
      \param nbConn number of SQL concurrent connection
    */
    static bool sqlConnect(QString dbName, QString hostname, QString username, QString password, QString driver, int port, int nbConn);
private:
    //! Mutex for single access to Array of available connection
    static QMutex mymute;
    //! Semaphore for single access socket to database
    static QSemaphore mtsema;
    //! Map of status of SQL connections
    static  QHash<QByteArray, bool> map;
};

#endif
