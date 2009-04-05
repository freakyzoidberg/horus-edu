#include "ClientSocket.h"

ClientSocket::ClientSocket(QObject *parent) : QTcpSocket(parent)
{
}

void ClientSocket::readPendingDatagrams()
{
    this->write("receve");
    qDebug() << "receve";
}
