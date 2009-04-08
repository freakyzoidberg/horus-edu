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
    void onReceve();
};

#endif // SOCKET_H
