#include "MailSmtpDataBase.h"


MailSmtpDataBase::MailSmtpDataBase( const QString &from, const QString &to,
            const QString &subject,
            const QString &body )
{
    socket = new QTcpSocket( this );
    connect ( socket, SIGNAL( readyRead() ),
              this, SLOT(readyRead()) );
    connect ( socket, SIGNAL( connected() ),
              this, SLOT(connected()) );

    //mxLookup = new QHostInfo(QHostInfo::fromName( )));
    QHostInfo info = QHostInfo::fromName(to.mid( to.indexOf( '@' )+1 ));
    socket->connectToHost(QHostAddress(info.addresses().first()), 25 );
    t = new QTextStream( socket );
    //connect(QObject(mxLookup), SIGNAL(resultsReady()),
      //       this, SLOT(dnsLookupHelper()) );

    message = QString::fromLatin1( "From: " ) + from +
              QString::fromLatin1( "\nTo: " ) + to +
              QString::fromLatin1( "\nSubject: " ) + subject +
              QString::fromLatin1( "\n\n" ) + body + "\n";
    message.replace( QRegExp( QString::fromLatin1( "\n" ) ),
                     QString::fromLatin1( "\r\n" ) );
    message.replace( QRegExp( QString::fromLatin1( "\r\n.\r\n" ) ),
                     QString::fromLatin1( "\r\n..\r\n" ) );

    this->from = from;
    rcpt = to;

    state = Init;
}


MailSmtpDataBase::~MailSmtpDataBase()
{
    delete t;
    delete socket;
}

void MailSmtpDataBase::connected()
{
    emit status( tr( "Connected to %1" ).arg( socket->peerName() ) );
}


void MailSmtpDataBase::readyRead()
{
    // SMTP is line-oriented
    if ( !socket->canReadLine() )
        return;

    QString responseLine;
    do {
        responseLine = socket->readLine();
        response += responseLine;
    } while( socket->canReadLine() && responseLine[3] != ' ' );
    responseLine.truncate( 3 );

    if ( state == Init && responseLine[0] == '2' ) {
        // banner was okay, let's go on
        *t << "HELO there\r\n";
        state = Mail;
    } else if ( state == Mail && responseLine[0] == '2' ) {
        // HELO response was okay (well, it has to be)
        *t << "MAIL FROM: <" << from << ">\r\n";
        state = Rcpt;
    } else if ( state == Rcpt && responseLine[0] == '2' ) {
        *t << "RCPT TO: <" << rcpt << ">\r\n";
        state = Data;
    } else if ( state == Data && responseLine[0] == '2' ) {
        *t << "DATA\r\n";
        state = Body;
    } else if ( state == Body && responseLine[0] == '3' ) {
        *t << message << ".\r\n";
        state = Quit;
    } else if ( state == Quit && responseLine[0] == '2' ) {
        *t << "QUIT\r\n";
        // here, we just close.
        state = Close;
        emit status( tr( "Message sent" ) );
    } else if ( state == Close ) {
        delete this;
        return;
    } else {
        // something broke.

        qDebug() << "Unexpected reply from SMTP server:\n\n";
        qDebug() << response;
        state = Close;
    }

    response = "";
}
