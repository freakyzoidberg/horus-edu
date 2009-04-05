#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QString>
#include <QTcpSocket>
#include <QtDebug>
#include <QThreadPool>

#include "../Common/CommInit.h"
#include "../Common/CommLogin.h"
#include "../Common/CommModule.h"
#include "../Common/CommRequest.h"

class ClientSocket : public QTcpSocket
{
  Q_OBJECT

public:
    ClientSocket(QObject *parent = 0);
    QDataStream stream;

public slots:
    void onRecvLogin();
    void onRecvRequest();
};

#endif // CLIENTSOCKET_H
