#include "Server.h"
#include "Sql.h"
#include "ThreadFiles.h"
#include "../Common/Defines.h"
#include "ClientSocket.h"
#include "Settings.h"
#include "Tree.h"
Server::Server(QObject *parent) : QTcpServer(parent)
{
    // Server mysql a configurer
    Settings *config = new Settings();
    config->CheckSettings();
    if (Sql::sqlConnect(config->GetSettings("SQL_DBNAME","SQL"), config->GetSettings("SQL_HOSTNAME","SQL"), config->GetSettings("SQL_USERNAME","SQL"), config->GetSettings("SQL_PASSWD","SQL"), config->GetSettings("SQL_DRIVER","SQL"), config->GetSettings("SQL_PORT","SQL").toInt(), SQLCONNECTIONCOUNT))
        qDebug() << "Server::Server() SQL connected";
    else
        qDebug() << "Server::Server() NO SQL !!!";

    new ThreadFiles(this);
    Tree::UpdateVector();
    //update tree

    //QSettings settings;
    if (listen(QHostAddress::Any, config->GetSettings("SRV_PORT","SERVER").toInt()))
        qDebug() << "Server Listening on port:" << serverPort();
    else
        qDebug() << "Server Not listening" << errorString();
}

void Server::incomingConnection(int socket)
{
    /* /!\ don't save the returned value
     *  ClientSocket will destruct himself
     */
    new ClientSocket(socket, this);
}
