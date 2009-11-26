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
#include "Server.h"
#include "Sql.h"
#include "../Common/Defines.h"
#include "ClientSocket.h"
#include "Settings.h"
#include "../Common/Logs.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{
    // Server mysql a configurer
    Settings *config = new Settings();
    config->CheckSettings();

    logs *mylog = new logs();
    QDateTime now = QDateTime::currentDateTime();
    mylog->setFile(config->GetSettings("SoftFullPath","SETTINGS"), "Logs-Server-"+now.toString("d-MMM-yy_h-mm-ss")+".log");
    mylog->start();

    if (Sql::sqlConnect(config->GetSettings("SQL_DBNAME","SQL"), config->GetSettings("SQL_HOSTNAME","SQL"), config->GetSettings("SQL_USERNAME","SQL"), config->GetSettings("SQL_PASSWD","SQL"), config->GetSettings("SQL_DRIVER","SQL"), config->GetSettings("SQL_PORT","SQL").toInt(), SQLCONNECTIONCOUNT))
    {
        //mylog->addlog(LOGINFO,"Connected to SQL Server");
        logs::addlog(LOGINFO,"Connected to SQL Server");
        //qDebug() << "Server::Server() SQL connected";
    }
    else
    {
        mylog->addlog(LOGERROR,"Problem while connecting to SQL Server");
        qCritical() << "Problem while connecting to SQL Server";
    }
        //qDebug() << "Server::Server() NO SQL !!!";

    //QSettings settings;
    if (listen(QHostAddress::Any, config->GetSettings("SRV_PORT","SERVER").toInt()))
        mylog->addlog(LOGINFO,"Server Listening on port:" + QVariant(serverPort()).toString());
    else
        mylog->addlog(LOGERROR,"Server Not listening : " + errorString());

}

void Server::incomingConnection(int socket)
{
    /* /!\ don't save the returned value
     *  ClientSocket will destruct himself
     */
    new ClientSocket(socket, this);
}
