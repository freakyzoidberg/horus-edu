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
#ifndef LHPOP_3_H
#define LHPOP_3_H

#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QAuthenticator>
#include <QSslSocket>
#include "mail.h"


class Pop_3 : public QObject {
 Q_OBJECT

public:

        Pop_3 (const QString &user,const QString &passwd, const QString &pop3_server,QObject *parent=0);
        QList<Mail*> getAllMail(int MaxMail);
        ~Pop_3();
        bool run();

        int getTotalmsg() { return _totalmsg;}

private slots:
    void errorReceived(QAbstractSocket::SocketError socketError);
    //void proxyAuthentication(const QNetworkProxy & proxy, QAuthenticator * authenticator);



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
