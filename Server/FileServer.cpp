#include "FileServer.h"

#include <QSettings>

//FileServer* FileServer::instance = 0;

FileServer::FileServer()
{
/*    if (instance)
    {
        qDebug() << "error, FileServer already instancied.";
        return;
    }
    instance = this;
*/
    QSettings config;
    if (listen(QHostAddress::Any, config.value("SERVER/FILE_TRANSFERT_PORT", 42042).toInt()))
        qDebug() << "FileServer Listening on port:" << serverPort();
    else
        qDebug() << "FileServer Not listening:" << errorString();

//    connect(this, SIGNAL(registerFileTransfertSignal(QByteArray,FileTransfert*)), this, SLOT(registerFileTransfertSlot(QByteArray,FileTransfert*)), Qt::QueuedConnection);
}

void FileServer::incomingConnection(int socket)
{
    qDebug() << "FileServer::incommingConnection";
    // Don't save the returned value, autodestructive object
//    new FileTransfert(socket, this);
}
/*
void FileServer::registerFileTransfert(const QByteArray& key, FileTransfert* ft)
{
    emit FileServer::instance->registerFileTransfertSignal(key, ft);
}

void FileServer::registerFileTransfertSlot(const QByteArray& key, FileTransfert* ft)
{
    transferts[ key ] = ft;
}
*/
