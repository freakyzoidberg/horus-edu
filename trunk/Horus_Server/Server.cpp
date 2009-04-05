#include "Server.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{
    /* Server mysql a configurer
    sql *fddb = new sql();

    if (fddb->sqlconnect("testhorus", "219.221.96.19", "horus", "horuspwd"))
        qDebug() << "Ohoho Connecte sur mysql@219.221.96.19";
    else
        qDebug() << "arf pas de sql";
    */

    this->listen(QHostAddress::Any, 42421);
    this->check();
}

void Server::incomingConnection(int socket)
{
    ClientSocket* cli = new ClientSocket();
    if (!cli->setSocketDescriptor(socket))
    {
        //emit error(cli.error());
        return;
    }
    cli->write("COUCOU!!");
    cli->connect(cli, SIGNAL(readyRead()), SLOT(readPendingDatagrams()));
    this->clients << cli;

    //QThreadPool::globalInstance()->start(cli);
//    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
}

void Server::check()
{
    if (!this->isListening())
        qDebug() << "Server Dont Listen";
    else
        qDebug("Server Listen on port : %d", this->serverPort());
}

