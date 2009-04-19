#ifndef COMMSOCKET_H
#define COMMSOCKET_H

#include <QSsl>
#include <QSslSocket>

class CommSocket : public QSslSocket
{
  Q_OBJECT
public:
    CommSocket(QObject* parent = 0);

private:
    quint32 sizePacket;

private slots:
    void ready();
    void bytesReceived();

    void errorSlot(QAbstractSocket::SocketError e);
    void sslErrorsSlot(QList<QSslError> e);
    void modeChangedSlot ( QSslSocket::SslMode e );
    void peerVerifyErrorSlot ( const QSslError & e );

protected slots:
    void sendPacket(const QByteArray&);

signals:
    void packetReceived(const QByteArray&);
};

#endif // COMMSOCKET_H
