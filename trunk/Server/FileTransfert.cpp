#include "FileTransfert.h"

#include <QTime>

#include "../Common/Defines.h"
#include "ThreadFiles.h"

QHash<QByteArray,FileTransfert*> FileTransfert::transferts;

FileTransfert::FileTransfert(QFile* _file)
{
    qDebug() << "FileTransfert(...)";
    file = _file;
    file->setParent(this);
    timer = new QTimer(this);
    socket = 0;

    //TODO maybe change this value
    qsrand(QTime::currentTime().msec());
    for (int i = 0; i < FILE_TRANSFERT_KEY_SIZE; i++)
        key[i] = qrand();

    moveToThread(ThreadFiles::instance());

    connect(this, SIGNAL(start()), this, SLOT(startSlot()), Qt::QueuedConnection);
    emit start();
}

void FileTransfert::startSlot()
{
    disconnect(this, SLOT(startSlot()));
    connect(timer, SIGNAL(timeout()), this, SLOT(deleteLater()));
    transferts.insert(key, this);
    // 1second for tests
    timer->start(FILE_TRANSFERT_WAIT_TIME * 1000);
}

void FileTransfert::read()
{
    file->write(socket->read(4086));
}

void FileTransfert::write(qint64)
{
    socket->write(file->read(4086));
}

const QByteArray& FileTransfert::getKey() const
{
    return key;
}

void FileTransfert::clientConnected(QSslSocket* _socket)
{
    socket = _socket;
    qDebug() << "FileTransfert::clientConnected";
    disconnect(timer, SIGNAL(timeout()), 0, 0);
    connect(socket, SIGNAL(disconnected()), this, SLOT(deleteLater()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(write(qint64)));
    write(0);
}

FileTransfert::~FileTransfert()
{
    delete timer;
    delete file;
    transferts.remove(key);
    qDebug() << "~FileTransfert()";
}

void FileTransfert::registerSocket(const QByteArray& key, QSslSocket* socket)
{
    FileTransfert* trans = transferts.value(key);
    if ( ! trans)
    {
        delete socket;
        return;
    }

    trans->clientConnected(socket);
}
