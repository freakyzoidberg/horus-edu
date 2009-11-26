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
#include "FileServer.h"
#include "FileTransfertServer.h"

#include "../../../Common/Defines.h"
#include "../../../Common/DataImplementations/FileDataBase/FileDataBasePlugin.h"

#include <QSettings>

FileServer* FileServer::instance()
{
    static FileServer _instance;
    return &_instance;
}

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
//    qDebug() << "FileServer::incommingConnection";
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

void FileServer::readKey()
{
//    qDebug() << "FileServer::readKey";
    QSslSocket* s = (QSslSocket*)(sender());
    if (s->bytesAvailable() < FILE_TRANSFERT_KEY_SIZE)
        return;

    s->disconnect(this, SLOT(readKey()));
	FileTransfertServer::registerSocket(s->read(FILE_TRANSFERT_KEY_SIZE), s);
}

void FileServer::errorSlot(QAbstractSocket::SocketError e)
{
	qDebug() << e;
}

void FileServer::sslErrorsSlot(QList<QSslError> e)
{
	qDebug() << e;
}
