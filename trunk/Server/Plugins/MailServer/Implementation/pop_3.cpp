#include "pop_3.h"
#include "mail.h"
#include <QVariant>
#include <QNetworkProxy>
Pop_3::Pop_3(const QString &user,const QString &passwd, const QString &pop3_server,QObject *parent)
{
       _port = 110;
    _timeout = 30000;
    _user = user;
    _passwd = passwd;
              _popServer = pop3_server;
}

Pop_3::~Pop_3()
{
}

void Pop_3::run()
{

    if (connectToPop(_popServer))
        qDebug() << "Connected to POP3";
    else
    {
        qDebug() << "Error - Connecting to POP3";
        return;
    }
    if (LogintoPop(_user, _passwd))
        qDebug() << "Authed to POP3";
    else
    {
        qDebug() << "Error - Authing to POP3";
        return;
    }
    if (getStat())
        qDebug() << "Stated POP3";
    else
    {
        qDebug() << "Error - Cannot Stat POP3";
        return;
    }

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

    QNetworkProxy proxy;
    proxy.setType(QNetworkProxy::Socks5Proxy);
    proxy.setHostName("proxies.epitech.net");
    proxy.setPort(1080);
    proxy.setUser("bertho_r");
    proxy.setPassword("pDewqw3(");
    QNetworkProxy::setApplicationProxy(proxy);

    _socket.data()->setProxy(proxy);

    //_socket=new QTcpSocket(this);
    connect( _socket, SIGNAL( error( QAbstractSocket::SocketError) ), this, SLOT( errorReceived( QAbstractSocket::SocketError ) ) );
    connect( _socket, SIGNAL( proxyAuthenticationRequired(const QNetworkProxy & , QAuthenticator *) ), this, SLOT(proxyAuthentication(const QNetworkProxy &, QAuthenticator * ) ) );

    qDebug() << "connect pop";
    bool auth = ! _user.isEmpty();

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

bool Pop_3::readMail(int size)
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
               qDebug() << _lastResponse.split(" ").at(1).toUInt() << " Buffer : " << _socket->readBufferSize();
               readMail(_lastResponse.split(" ").at(1).toUInt());

               Mail* mail = new Mail();

               mail->setuid(uid);
               mail->setData(_lastResponse);
               panier.append(mail);
           }
       }
    }
    return panier;
}

