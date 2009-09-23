#include <QThreadPool>
#include <QDebug>
#include <QDir>
#include "ClientSocket.h"
#include "ThreadPacket.h"
#include "../Common/Defines.h"
#include "../Common/CommInit.h"
#include "Settings.h"
#include "../Common/Logs.h"

quint32 ClientSocket::nbCon = 0;
QHash<UserData*,ClientSocket*> ClientSocket::connectedUsers;


ClientSocket::ClientSocket(int _socket, QObject* parent)
    : CommSocket(parent)
{
    static quint32 newId = 0;
    nbCon++;
    id = newId++;
    logs::addlog(LOGINFO, "New client connected " + QVariant(id).toString());
    //qDebug() << "-----Client" << id << "connected";

    threads.release();//1
    nbThreads = 0;
    status = INIT;

    user = 0;
    //connect(&user, SIGNAL(sendPacketSignal(const QByteArray&)), this, SLOT(sendPacket(const QByteArray&)));
    connect(this,  SIGNAL(packetReceived(const QByteArray&)),   this, SLOT(packetAvailable(const QByteArray&)));
    connect(this,  SIGNAL(encrypted()),                         this, SLOT(ready()));
    connect(this,  SIGNAL(disconnected()),                      this, SLOT(tryToDelete()));
    Settings config;
    setLocalCertificate(config.GetSettings("SoftFullPath","SETTINGS") + QDir::toNativeSeparators("./ssl/Horus.crt"));
    setPrivateKey(config.GetSettings("SoftFullPath","SETTINGS") + QDir::toNativeSeparators("./ssl/Horus.key"));
    setSocketDescriptor(_socket);
    startServerEncryption();
}

ClientSocket::~ClientSocket()
{
    nbCon--;
    if (user)
        connectedUsers.remove(user);
    logs::addlog(LOGINFO, "Client disconnected " + QVariant(id).toString() + ", There is " + QVariant(nbCon).toString() + " users left");
    //qDebug() << "-----Client"<< id << "disconected. there's still" << nbCon << "users";
    close();
}


void ClientSocket::ready()
{
//    disconnect(this, SIGNAL(encrypted()), 0, 0);
//    connect(this, SIGNAL(packetReceived(QByteArray)), this, SLOT(packetAvailable(QByteArray)));

    // Send the CommInit packet
    CommInit init(CURRENT_PROTO_VERSION, SERVER_NAME);
    sendPacket(init.getPacket());
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
    if ( ! nbThreads && ! recvQueue.count())
        deleteLater();
}
