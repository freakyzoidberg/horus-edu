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
