#ifndef COMMSOCKET_H
#define COMMSOCKET_H

#include <QSslSocket>

//! Communication socket is a QSslSocket, shared onto Client and Server
class CommSocket : public QSslSocket
{
  Q_OBJECT
public:
    CommSocket(QObject* parent = 0);

private:
    //! size of the next packet to read
    /*! each packet is preceded by an uint32 containing the size of the packet
     *  while this size is not into the read buffer(QTcpSocket::byteAvailables()), nothing is read
     */
    quint32 sizePacket;

private slots:
    //! slot connected with QTcpSocket::readyRead(): when so data just arrived
    void bytesReceived();

    //! slot connected with QTcpSocket::error(): when an error occur on the socket
    void errorSlot(QAbstractSocket::SocketError e);
    //! slot connected with QSslSocket::sslErrors(): when an ssl error occur on the socket
    void sslErrorsSlot(QList<QSslError> e);

public slots:
    //! slot to send packet to a client
    void sendPacket(const QByteArray&);

signals:
    //! signal emmitted when a packet is received
    void packetReceived(const QByteArray&);
};

#endif // COMMSOCKET_H
