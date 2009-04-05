#include "ClientSocket.h"

ClientSocket::ClientSocket(QObject *parent) : QTcpSocket(parent)
{
    stream.setDevice(this);
}

void ClientSocket::onRecvLogin()
{
    CommLogin msg("0.1.2", "toto42");

    stream << msg; //envoi o lieu de recevoir pour test et voir cqui sort

    disconnect(this, SIGNAL(readyRead()), 0, 0);
       connect(this, SIGNAL(readyRead()), SLOT(onRecvRequest()));
}

void ClientSocket::onRecvRequest()
{
    write("recu request");
    qDebug() << "recu request";
}
