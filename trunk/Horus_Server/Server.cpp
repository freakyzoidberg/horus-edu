#include "Server.h"
#include "Thread.h"
#include "sql.h"
#include <stdlib.h>

Server::Server(QObject *parent) : QTcpServer(parent)
{
    sql *fddb = new sql();
    /* Server mysql a configurer
    if (fddb->sqlconnect("testhorus", "219.221.96.19", "horus", "horuspwd"))
        qDebug() << "Ohoho Connecte sur mysql@219.221.96.19";
    else
        qDebug() << "arf pas de sql";
    */
    this->listen(QHostAddress::Any, 42421);
    this->OptionalFill();
    this->check();
}

void Server::incomingConnection(int socketDescriptor)
{
    QString fortune = fortunes.at(qrand() % fortunes.size());
        qDebug() << "new Client" << socketDescriptor;
    Thread *thread = new Thread(socketDescriptor, fortune, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void Server::OptionalFill()
{
    fortunes << tr("You've been leading a dog's life. Stay off the furniture.")
             << tr("You've got to think about tomorrow.")
             << tr("You will be surprised by a loud noise.")
             << tr("You will feel hungry again in another hour.")
             << tr("You might have mail.")
             << tr("You cannot kill time without injuring eternity.")
             << tr("Computers are not intelligent. They only think they are.");
}

void Server::check()
{
    if (!this->isListening())
        qDebug() << "Server Dont Listen";
    else
        qDebug("Server Listen on port : %d", this->serverPort());
}

