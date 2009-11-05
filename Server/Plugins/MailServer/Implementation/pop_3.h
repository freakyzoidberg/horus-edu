#ifndef LHPOP_3_H
#define LHPOP_3_H

#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QAuthenticator>
#include <QSslSocket>
#include "mail.h"


class Pop_3 : public QThread {

        Q_OBJECT

public:

        Pop_3 (const QString &user,const QString &passwd, const QString &pop3_server,QObject *parent=0);
        QList<Mail*> getAllMail(int MaxMail);
        ~Pop_3();
        void run();

        int getTotalmsg() { return _totalmsg;}

private slots:
    void errorReceived(QAbstractSocket::SocketError socketError);
    void proxyAuthentication(const QNetworkProxy & proxy, QAuthenticator * authenticator);


private:
    bool connectToPop(const QString &host);
    bool LogintoPop(const QString login, const QString passwd);
    bool getStat();

    void error(const QString &msg);
    bool read(const QString &waitfor);
    bool readMail(int size);
    bool sendCommand(const QString &cmd, const QString &waitfor);
    bool sendRetr(const QString &cmd);






    QString        _popServer;
    int         _port;
    int         _timeout;
    QString     _user;
    QString     _passwd;
    QPointer<QTcpSocket>  _socket;
    bool        _ssl;
    QAuthenticator _authenticator;
    QString     _lastError;
    QString     _lastCmd;
    QString     _lastResponse;
    QString     _lastMailData;
    int         _totalmsg;
    int         _totalsize;

};

#endif
