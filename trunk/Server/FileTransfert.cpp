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
}

void FileTransfert::write()
{
}

const QByteArray& FileTransfert::getKey()
{
    return key;
}

void FileTransfert::clientConnected(QSslSocket* _socket)
{
    socket = _socket;
    qDebug() << "FileTransfert::clientConnected";
    disconnect(timer, SIGNAL(timeout()), 0, 0);
    connect(socket, SIGNAL(disconnected()), this, SLOT(deleteLater()));
    transferts.remove(key);
}

FileTransfert::~FileTransfert()
{
    delete timer;
    delete file;
    if (socket)
        delete socket;
    transferts.remove(key);
    transferts.remove(key);
    qDebug() << "~FileTransfert()";
}
