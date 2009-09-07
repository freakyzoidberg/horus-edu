#include "Server.h"
#include "Sql.h"
#include "../Common/Defines.h"
#include "ClientSocket.h"
#include "Settings.h"
#include "Logs.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{
    // Server mysql a configurer
    Settings *config = new Settings();
    config->CheckSettings();

    logs *mylog = new logs();
    QDateTime now = QDateTime::currentDateTime();
    mylog->setFile(config->GetSettings("SoftFullPath","SETTINGS")+"/"+"Logs-Server-"+now.toString("d-MMM-yy_h-mm-ss")+".log");
    mylog->start();

    if (Sql::sqlConnect(config->GetSettings("SQL_DBNAME","SQL"), config->GetSettings("SQL_HOSTNAME","SQL"), config->GetSettings("SQL_USERNAME","SQL"), config->GetSettings("SQL_PASSWD","SQL"), config->GetSettings("SQL_DRIVER","SQL"), config->GetSettings("SQL_PORT","SQL").toInt(), SQLCONNECTIONCOUNT))
    {
        mylog->addlog(LOGINFO,"Connected to SQL Server");
        //qDebug() << "Server::Server() SQL connected";
    }
    else
        mylog->addlog(LOGERROR,"Problem while connecting to SQL Server");
        //qDebug() << "Server::Server() NO SQL !!!";


    //QSettings settings;
    if (listen(QHostAddress::Any, config->GetSettings("SRV_PORT","SERVER").toInt()))
        mylog->addlog(LOGINFO,"Server Listening on port:" + QString(serverPort()));
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
