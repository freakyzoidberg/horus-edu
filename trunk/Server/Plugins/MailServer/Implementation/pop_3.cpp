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
#include "pop_3.h"
#include "mail.h"
#include <QVariant>
#include <QNetworkProxy>
Pop_3::Pop_3(const QString &user,const QString &passwd, const QString &pop3_server,QObject *)
{
       _port = 110;
    _timeout = 10000;
    _user = user;
    _passwd = passwd;
    _popServer = pop3_server;
}

Pop_3::~Pop_3()
{
}

bool Pop_3::run()
{

    if (connectToPop(_popServer))
        qDebug() << "Connected to POP3";
    else
    {
        qDebug() << "Error - Connecting to POP3";
        return false;
    }
    if (LogintoPop(_user, _passwd))
        qDebug() << "Authed to POP3";
    else
    {
        qDebug() << "Error - Authing to POP3";
        return false;
    }
    if (getStat())
        qDebug() << "Stated POP3";
    else
    {
        qDebug() << "Error - Cannot Stat POP3";
        return false;
    }
return true;
}

void Pop_3::errorReceived(QAbstractSocket::SocketError socketError)
{
    QString msg;

    switch(socketError) {
        case QAbstractSocket::ConnectionRefusedError: msg = "ConnectionRefusedError"; break;
        case QAbstractSocket::RemoteHostClosedError: msg = "RemoteHostClosedError"; break;
        case QAbstractSocket::HostNotFoundError: msg = "HostNotFoundError"; break;
        case QAbstractSocket::SocketAccessError: msg = "SocketAccessError"; break;
        case QAbstractSocket::SocketResourceError: msg = "SocketResourceError"; break;
        case QAbstractSocket::SocketTimeoutError: msg = "SocketTimeoutError"; break;
        case QAbstractSocket::DatagramTooLargeError: msg = "DatagramTooLargeError"; break;
        case QAbstractSocket::NetworkError: msg = "NetworkError"; break;
        case QAbstractSocket::AddressInUseError: msg = "AddressInUseError"; break;
        case QAbstractSocket::SocketAddressNotAvailableError: msg = "SocketAddressNotAvailableError"; break;
        case QAbstractSocket::UnsupportedSocketOperationError: msg = "UnsupportedSocketOperationError"; break;
        case QAbstractSocket::ProxyAuthenticationRequiredError: msg = "ProxyAuthenticationRequiredError"; break;
        default: msg = "Unknown Error";
    }

    error("Socket error [" + msg + "]");
}

void Pop_3::error(const QString &msg)
{
    qDebug() << msg;
}

bool Pop_3::connectToPop(const QString &host)
{
    _lastError = "";

    if(_socket)
    {
        delete _socket;
    }

    _socket = _ssl ? new QSslSocket(this) : new QTcpSocket(this);
/*
    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::Socks5Proxy);
    proxy.setHostName("10.42.42.62");
    proxy.setPort(1080);
    proxy.setUser("bertho_r");
    proxy.setPassword("pDewqw3(");

    _socket.data()->setProxy(proxy);
*/
    //_socket=new QTcpSocket(this);
    connect( _socket, SIGNAL( error( QAbstractSocket::SocketError) ), this, SLOT( errorReceived( QAbstractSocket::SocketError ) ) );
    //connect( _socket, SIGNAL( proxyAuthenticationRequired(const QNetworkProxy & , QAuthenticator *) ), this, SLOT(proxyAuthentication(const QNetworkProxy &, QAuthenticator * ) ) );

    qDebug() << "connect pop";
    //bool auth = ! _user.isEmpty();

    _socket->connectToHost( host, _port );

    qDebug() << "connected ?";
    if( !_socket->waitForConnected( _timeout ) )
    {
        error("Time out connecting host");
        return false;
    }

    if(!read("+OK")) {
        qDebug() << "pas +OK";
        return false;
    }
    return true;
}

bool Pop_3::read(const QString &waitfor)
{
    if( ! _socket->waitForReadyRead( _timeout ) ) {
        error("Read timeout");
        return false;
    }

    if( !_socket->canReadLine() ) {
        error("Can't read");
        return false;
    }

    QString responseLine;

    do {
        responseLine = _socket->readLine();
    } while( _socket->canReadLine() && responseLine[3] != ' ' );

    _lastResponse = responseLine;

    QString prefix = responseLine.left(3);
    bool isOk = (prefix == waitfor);
    if(!isOk) {
        error("waiting for " + waitfor + ", received " + prefix);
    }
    return isOk;
}

bool Pop_3::readMail(int)
{
QString response;
    QString responseLine;


    do {

        
        if( ! _socket->waitForReadyRead( _timeout ) ) {
        error("Read timeout");
        return false;
    }

    if( !_socket->canReadLine() ) {
        error("Can't read");
        return false;
    }
        do {
            responseLine = _socket->readLine();
            response += responseLine;
        //qDebug() << responseLine.size() << " " <<responseLine;
        } while( _socket->canReadLine() && responseLine != ".\r\n" );
    } while (responseLine != ".\r\n");



_lastResponse = response;
    //qDebug() << _lastResponse;
	return (true);
}


bool Pop_3::sendCommand(const QString &cmd, const QString &waitfor)
{
    qDebug() << "sending -- " << cmd;
    QTextStream t(_socket);
    t << cmd + "\r\n";
    t.flush();

    _lastCmd = cmd;

    return read(waitfor);
}

bool Pop_3::sendRetr(const QString &cmd)
{
    qDebug() << "sending -- " << cmd;
    QTextStream t(_socket);
    t << cmd + "\r\n";
    t.flush();

    _lastCmd = cmd;

    return true;
}


bool Pop_3::LogintoPop(const QString login, const QString passwd)
{

     if ( !sendCommand("USER " + login, "+OK") )
    {
            return false;
    }
     if ( !sendCommand("PASS " + passwd, "+OK") )
    {
            return false;
    }
    return true;
}

bool Pop_3::getStat()
{
    if ( !sendCommand("STAT", "+OK") )
    {
            return false;
    }

    QStringList sl = _lastResponse.split(" ");

        _totalmsg = sl.at(1).toUInt();
        _totalsize = sl.at(2).toUInt();

    return true;
}


QList<Mail*> Pop_3::getAllMail(int MaxMail)
{
    int i;
    QString uid;
    QList<Mail*> panier;
    for (i = 1; i <= MaxMail; i++)
    {
       if (!sendCommand("UIDL " + QVariant(i).toString(), "+OK"))
       {
            qDebug() << "Error";
           return panier;
       }
       else
       {

            uid = _lastResponse.split(" ").at(2);

            sendRetr("RETR " + QVariant(i).toString());
           if  (!read("+OK"))
              return panier;
           else
           {
           qDebug() << "le +ok :" <<_lastResponse;
               //qDebug() << _lastResponse.split(" ").at(1).toUInt() << " Buffer : " << _socket->readBufferSize();
               //qDebug() << _lastResponse.split(" ").at(1).toUInt();
               readMail(_lastResponse.split(" ").at(1).toUInt());

               Mail* mail = new Mail();

               mail->setuid(uid);
               mail->setData(_lastResponse);
               qDebug() << "mail   data: "<< mail->getShowText();
               //mail->parseData(_lastResponse);
               qDebug() << _lastResponse;
               panier.append(mail);
           }
       }
    }
    return panier;
}

