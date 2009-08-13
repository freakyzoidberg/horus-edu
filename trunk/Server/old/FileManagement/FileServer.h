#ifndef FILESERVER_H
#define FILESERVER_H

#include <QSslSocket>
#include <QTcpServer>

//! a QTcpServer, to wait for file transfert connexions
class FileServer : public QTcpServer
{
  Q_OBJECT
public:
    FileServer();

protected:
    //! when a new connexion is openned
    void incomingConnection (int socket);

private slots:
    void readKey();
    //! slot connected with QTcpSocket::error(): when an error occur on the socket
    void errorSlot(QAbstractSocket::SocketError e);
    //! slot connected with QSslSocket::sslErrors(): when an ssl error occur on the socket
    void sslErrorsSlot(QList<QSslError> e);
};

#endif // FILESERVER_H
