#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QString>
#include <QTcpSocket>
#include <QtDebug>

//#include "../Common/ConnexionMessage.h"

class ClientSocket : public QTcpSocket
{
  Q_OBJECT

public:
    ClientSocket(QObject *parent = 0);

//    void            SendData(QString mod, void* data, int size);

//signals:
//    void  readyRead();

public slots:
    void readPendingDatagrams();

private:
    enum status {NEW, AUTH, END};
};

#endif // CLIENTSOCKET_H
