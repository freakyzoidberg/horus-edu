#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QString>
#include <QTcpSocket>
#include <QtDebug>

#include "../Common/CommInit.h"
#include "../Common/CommLogin.h"
#include "../Common/CommModule.h"
#include "../Common/CommRequest.h"

class ClientSocket : public QTcpSocket
{
  Q_OBJECT

public:
    ClientSocket(QObject *parent = 0);

public slots:
    void onRecvLogin();
    void onRecvRequest();

private:
    QDataStream stream;
};

#endif // CLIENTSOCKET_H
