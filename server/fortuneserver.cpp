#include "fortuneserver.h"
#include "fortunethread.h"

#include <stdlib.h>

FortuneServer::FortuneServer(QObject *parent) : QTcpServer(parent)
{
    this->listen(QHostAddress::Any, 42421);
    this->OptionalFill();
    this->check();
}

void FortuneServer::incomingConnection(int socketDescriptor)
{
    QString fortune = fortunes.at(qrand() % fortunes.size());
        qDebug() << "new Client" << socketDescriptor;
    FortuneThread *thread = new FortuneThread(socketDescriptor, fortune, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void FortuneServer::OptionalFill()
{
    fortunes << tr("You've been leading a dog's life. Stay off the furniture.")
             << tr("You've got to think about tomorrow.")
             << tr("You will be surprised by a loud noise.")
             << tr("You will feel hungry again in another hour.")
             << tr("You might have mail.")
             << tr("You cannot kill time without injuring eternity.")
             << tr("Computers are not intelligent. They only think they are.");
}

void FortuneServer::check()
{
    if (!this->isListening())
        qDebug() << "Server Dont Listen";
    else
        qDebug() << "Server Listen on port";
    qDebug("port : %d", this->serverPort());

}
