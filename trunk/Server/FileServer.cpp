#include "FileServer.h"

#include <QSettings>
#include <QSslSocket>

FileServer::FileServer()
{
    QSettings config;
    if (listen(QHostAddress::Any, config.value("SERVER/FILE_TRANSFERT_PORT", 42042).toInt()))
        qDebug() << "FileServer Listening on port:" << serverPort();
    else
        qDebug() << "FileServer Not listening:" << errorString();
}

void FileServer::incomingConnection(int socket)
{
    qDebug() << "FileServer::incommingConnection";
    QSslSocket* s = new QSslSocket(this);

    s->setProtocol(QSsl::SslV3);

    //For test
    s->setPeerVerifyMode(QSslSocket::VerifyNone);

    s->setLocalCertificate("./ssl/Horus.crt");
    s->setPrivateKey("./ssl/Horus.key");

    connect(s, SIGNAL(readyRead()), this, SLOT(readKey()));

    s->setSocketDescriptor(socket);

    s->startServerEncryption();
}

void FileServer::readKey()
{
}
