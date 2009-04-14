#ifndef SOCKET_H
#define SOCKET_H

#include <QDebug>

#include "../Common/CommSocket.h"

class Socket : public CommSocket
{
  Q_OBJECT

public:
    Socket(const char*, quint16);
    QDataStream stream;

public slots:
    void packetAvailable(QByteArray);
    void stateChangedSlot(QAbstractSocket::SocketState);
};

#endif // SOCKET_H
