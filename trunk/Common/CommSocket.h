#ifndef COMMSOCKET_H
#define COMMSOCKET_H

#include <QTcpSocket>

class CommSocket : public QTcpSocket
{
  Q_OBJECT
public:
    CommSocket(QObject* parent = 0);

private:
    quint32 sizePacket;

private slots:
    void bytesReceived();

protected slots:
    void sendPacket(const QByteArray&);

signals:
    void packetReceived(const QByteArray&);
};

#endif // COMMSOCKET_H
