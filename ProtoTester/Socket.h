#ifndef SOCKET_H
#define SOCKET_H

#include <QDebug>
#include <QTcpSocket>

class Socket : public QTcpSocket
{
  Q_OBJECT

public:
    Socket(const char*, quint16);
    QDataStream stream;

public slots:
    void onReceve();
    void stateChangedSlot(QAbstractSocket::SocketState);
};

#endif // SOCKET_H
