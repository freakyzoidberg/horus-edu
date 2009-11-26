/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef SQL_H
#define SQL_H

#include <QtSql>
#include <QByteArray>
#include <QMutex>
#include <QSemaphore>
#include <QHash>

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
