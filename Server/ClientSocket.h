#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QString>
#include <QTcpSocket>
#include <QtDebug>
#include <QThreadPool>

#include "../Common/Defines.h"
#include "../Common/CommInit.h"
#include "../Common/CommLogin.h"
#include "../Common/CommModule.h"
#include "../Common/CommPacket.h"

class ClientSocket : public QTcpSocket
{
  Q_OBJECT

public:
    ClientSocket(QObject *parent = 0);
    ~ClientSocket();
    QDataStream stream;

public slots:
    void onReceveInit();
    void onRecevePacket();

private:
    quint32 id;
    static quint32 newId;
};

#endif // CLIENTSOCKET_H
