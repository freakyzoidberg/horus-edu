#ifndef COMMSOCKET_H
#define COMMSOCKET_H

#include <QTcpSocket>
#include <QMutex>

class CommSocket : public QTcpSocket
{
  Q_OBJECT
public:
    CommSocket(QObject* parent = 0);

public slots:
    void sendPacket(QByteArray);

//protected:
//
//private:
//    QList<QByteArray> sendQueue;

private:
    quint32 sizePacket;
    QMutex  sendQueueMutex;

private slots:
    void bytesReceived();
//    void sendPackets();

signals:
    void packetReceived(QByteArray);
//    void packetToSend();
};

#endif // COMMSOCKET_H
