#include "FileServer.h"

#include <QSettings>

#include "../../../Common/Defines.h"

#include "FileTransfert.h"

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

    connect(s, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorSlot(QAbstractSocket::SocketError)));
    connect(s, SIGNAL(sslErrors(QList<QSslError>)),         this, SLOT(sslErrorsSlot(QList<QSslError>)));

    s->setProtocol(QSsl::SslV3);

    //TODO later: For test
    s->setPeerVerifyMode(QSslSocket::VerifyNone);

    QSettings settings;
    s->setLocalCertificate(settings.value("SETTINGS/SoftFullPath").toString() + "./ssl/Horus.crt");
    s->setPrivateKey(settings.value("SETTINGS/SoftFullPath").toString() + "./ssl/Horus.key");

    s->connect(s, SIGNAL(readyRead()), this, SLOT(readKey()));

    // auto delete
    s->connect(s, SIGNAL(disconnected()), s, SLOT(deleteLater()));

    s->setSocketDescriptor(socket);

    s->startServerEncryption();
}

void FileServer::readKey()
{
    qDebug() << "FileServer::readKey";
    QSslSocket* s = (QSslSocket*)sender();
    if (s->bytesAvailable() < FILE_TRANSFERT_KEY_SIZE)
        return;

    s->disconnect(this, SLOT(readKey()));
    FileTransfert::registerSocket(s->read(FILE_TRANSFERT_KEY_SIZE), s);
}

void FileServer::errorSlot(QAbstractSocket::SocketError e)
{
    qDebug() << "error" << e;
}

void FileServer::sslErrorsSlot(QList<QSslError> e)
{
    qDebug() << "sslError" << e;
}
