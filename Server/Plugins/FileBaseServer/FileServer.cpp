#include "FileServer.h"
#include "FileTransfert.h"

#include "../../../Common/Defines.h"
#include "../../../Common/DataImplementations/FileDataBase/FileDataBasePlugin.h"

#include <QSettings>

FileServer::FileServer()
{
    if (listen(QHostAddress::Any, QSettings().value("SERVER/FILE_TRANSFERT_PORT", 42042).toInt()))
        qDebug() << "FileServer Listening on port:" << serverPort();
    else
        qDebug() << "FileServer Not listening:" << errorString();

    thread.start();
    moveToThread(&thread);
}

void FileServer::incomingConnection(int socket)
{
    qDebug() << "FileServer::incommingConnection";
    QSslSocket* s = new QSslSocket(this);

    connect(s, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorSlot(QAbstractSocket::SocketError)));
    connect(s, SIGNAL(sslErrors(QList<QSslError>)),         this, SLOT(sslErrorsSlot(QList<QSslError>)));

    connect(s, SIGNAL(readyRead()), this, SLOT(readKey()));
    // auto delete
    connect(s, SIGNAL(disconnected()), s, SLOT(deleteLater()));

    QString sslPath = QSettings().value("SETTINGS/SoftFullPath", ".").toString() + "/ssl";
    s->setLocalCertificate(sslPath + "/Horus.crt");
    s->setPrivateKey(sslPath + "/Horus.key");
    s->setProtocol(QSsl::SslV3);
    //TODO later: For test
    s->setPeerVerifyMode(QSslSocket::VerifyNone);
    s->setSocketDescriptor(socket);
    s->startServerEncryption();
}

void FileServer::readKey(QSslSocket* s)
{
    qDebug() << "FileServer::readKey";
//    QSslSocket* s = (QSslSocket*)(sender());
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
