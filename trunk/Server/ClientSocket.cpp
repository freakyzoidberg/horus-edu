#include "ClientSocket.h"
#include "ThreadPacket.h"
#include "../Common/Defines.h"
#include "../Common/CommInit.h"

quint32 ClientSocket::nbCon = 0;

ClientSocket::ClientSocket(int _socket, QObject* parent)
    : CommSocket(parent)
{
    static quint32 newId = 0;
    nbCon++;
    id = newId++;
    qDebug() << "-----Client" << id << "connected";

    threads.release();//1
    nbThreads = 0;
    userId = 0;
    vState = INIT;

    connect(this, SIGNAL(packetReceived(const QByteArray&)), this, SLOT(packetAvailable(const QByteArray&)));
    connect(this, SIGNAL(encrypted()), this, SLOT(ready()));
    connect(this, SIGNAL(disconnected()),                    this, SLOT(tryToDelete()));

    setSocketDescriptor(_socket);

    startServerEncryption();
}

ClientSocket::~ClientSocket()
{
    nbCon--;
    qDebug() << "-----Client"<< id << "disconected. there's still" << nbCon << "users";
    close();
}


void ClientSocket::ready()
{
//    disconnect(this, SIGNAL(encrypted()), 0, 0);
//    connect(this, SIGNAL(packetReceived(QByteArray)), this, SLOT(packetAvailable(QByteArray)));

    // Send the CommInit packet
    CommInit init(CURRENT_PROTO_VERSION, SERVER_NAME);
    sendPacket(init.getPacket());
    qDebug() << "[out]" << init;
}

void ClientSocket::packetAvailable(const QByteArray& pac)
{
    recvQueue.append(pac);
    tryToReadPacket();
}

void ClientSocket::tryToReadPacket()
{
    if (recvQueue.isEmpty())
        return;

    if ( ! threads.tryAcquire())
        return;
    nbThreads++;

    ThreadPacket* thread = new ThreadPacket(this, recvQueue.takeFirst());

    connect(thread, SIGNAL(sendPacket(const QByteArray&)), this, SLOT(sendPacket(const QByteArray&)));
    connect(thread, SIGNAL(destroyed()), this, SLOT(threadFinished()));

    QThreadPool::globalInstance()->start(thread);
    tryToReadPacket();
}

void ClientSocket::threadFinished()
{
    nbThreads--;
    threads.release();
    tryToReadPacket();
    if (state() == QTcpSocket::UnconnectedState)
        tryToDelete();
}

void ClientSocket::waitOtherThreads()
{
    while (threads.tryAcquire()) ;
    while (nbThreads > 1)
        threads.acquire();
}

void ClientSocket::allowOtherThreads()
{
    waitOtherThreads();
    threads.release(MAX_USER_THREADS - 1);
}

void ClientSocket::tryToDelete()
{
    if ( ! nbThreads && ! recvQueue.length())
        deleteLater();
}
