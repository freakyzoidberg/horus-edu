/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
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

	setLocalCertificate(config.GetSettings("SoftFullPath","SETTINGS") + QDir::toNativeSeparators("/ssl/Horus.crt"));
	setPrivateKey(config.GetSettings("SoftFullPath","SETTINGS") + QDir::toNativeSeparators("/ssl/Horus.key"));
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
