#include "Server.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{
    // Server mysql a configurer
    Settings *config = new Settings();

    if (Sql::sqlConnect(config->GetSettings("SQL_DBNAME","SQL"), config->GetSettings("SQL_HOSTNAME","SQL"), config->GetSettings("SQL_USERNAME","SQL"), config->GetSettings("SQL_PASSWD","SQL"), config->GetSettings("SQL_DRIVER","SQL"), config->GetSettings("SQL_PORT","SQL").toInt(), SQLCONNECTIONCOUNT))
        qDebug() << "Server::Server() SQL connected";
    else
        qDebug() << "Server::Server() NO SQL !!!";


    listen(QHostAddress::Any, config->GetSettings("SRV_PORT","SERVER").toInt());
    check();
}

void Server::incomingConnection(int socket)
{
    /* /!\ don't save the returned value
     *  ClientSocket will destruct himself
     */
    new ClientSocket(socket);
}

void Server::check()
{
    if ( !isListening())
        qDebug() << "Server::Server() Not listening";
    else
        qDebug("Server::Server() Listening on port : %d", serverPort());
}

