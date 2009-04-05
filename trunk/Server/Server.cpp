#include "Server.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{
    // Server mysql a configurer
    sql *fddb = new sql();
    Settings *config = new Settings();

    if (fddb->sqlconnect(config->GetSettings("SQL_DBNAME","SQL"), config->GetSettings("SQL_HOSTNAME","SQL"), config->GetSettings("SQL_USERNAME","SQL"), config->GetSettings("SQL_PASSWD","SQL"), config->GetSettings("SQL_DRIVER","SQL"), config->GetSettings("SQL_PORT","SQL")))
        qDebug() << "Server::Server() SQL connected";
    else
        qDebug() << "Server::Server() NO SQL !!!";


    listen(QHostAddress::Any, config->GetSettings("SRV_PORT","SERVER").toInt());
    check();
}

void Server::incomingConnection(int socket)
{
    ClientSocket* cli = new ClientSocket();
    if ( ! cli->setSocketDescriptor(socket))
    {
        //emit error(cli.error());
        return;
    }
    cli->write("COUCOU!! je suis Horus Server\nLogin et pass stp:");
    cli->connect(cli, SIGNAL(readyRead()), SLOT(onRecvLogin()));

    clients << cli;

    //QThreadPool::globalInstance()->start(cli);
//    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
}

void Server::check()
{
    if ( ! isListening())
        qDebug() << "Server::Server() Not listening";
    else
        qDebug("Server::Server() Listening on port : %d", serverPort());
}

