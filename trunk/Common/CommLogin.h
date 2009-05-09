#ifndef COMMLOGIN_H
#define COMMLOGIN_H

#include "CommPacket.h"

/*!
 * Response from the client to the server
 * after the first "ConnexionMessage" from the server
 */
class CommLogin : public CommPacket
{
public:
    /*!
     * Type of authenfication
     * in the future we may want to add the certificate auth. or something else
     */
    enum                lType{ UNDEFINED,
                               LOGIN_PASSWORD, LOGIN_SESSION, DESTROY_SESSION, //CLIENT  -> SERVER
                               ACCEPTED, REFUSED,                              // SERVER -> CLIENT
                               __LAST__ };

    CommLogin(lType);
    CommLogin(QByteArray&);

    const QByteArray    getPacket();

    lType               method;
    QString             login;
    QByteArray          sha1Pass;
    quint32             sessionTime;
    QByteArray          sessionString;

private:
    void                read(QByteArray&);
    void                write(QByteArray&);
};

QDebug operator<<(QDebug, CommLogin&);

#endif // COMMLOGIN_H
