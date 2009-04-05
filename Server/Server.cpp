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

    listen(QHostAddress::Any, 42421);
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
        qDebug() << "Server Dont Listen";
    else
        qDebug("Server Listen on port : %d", serverPort());
}

