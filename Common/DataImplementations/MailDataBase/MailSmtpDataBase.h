#ifndef MAILSMTPDATABASE_H
#define MAILSMTPDATABASE_H

#include <QObject>
#include <QString>
#include <QHostInfo>
#include <QTextStream>
#include <QTcpSocket>
#include <QTimer>
#include <QRegExp>

class MailSmtpDataBase : public QObject
{
    Q_OBJECT

public:
    MailSmtpDataBase( const QString &from, const QString &to,
          const QString &subject, const QString &body );
    ~MailSmtpDataBase();
    void status( const QString & );
    void readyRead();
    void connected();

private:
    enum State {
        Init,
        Mail,
        Rcpt,
        Data,
        Body,
        Quit,
        Close
    };

    QString message;
    QString from;
    QString rcpt;
    QTcpSocket *socket;
    QTextStream * t;
    int state;
    QString response;
    QHostInfo * mxLookup;
};

#endif
