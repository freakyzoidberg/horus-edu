#ifndef SOCKET_H
#define SOCKET_H

#include <QDebug>
#include <QTcpSocket>

class Socket : QTcpSocket
{
  Q_OBJECT

public:
    Socket(const char*, quint16);
    QDataStream stream;

public slots:
    void onReceveInit();
    void onRecevePacket();
};

#endif // SOCKET_H
