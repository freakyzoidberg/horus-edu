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
    //! type of authentification packet
    /*!
     * Type of authenfication
     * in the future we may want to add the certificate auth. or something else
     */
    enum                Method { UNDEFINED,
                                 LOGIN_PASSWORD, LOGIN_SESSION, DESTROY_SESSION, //CLIENT  -> SERVER
                                 ACCEPTED, REFUSED,                              // SERVER -> CLIENT
                                 __LAST__ };

    CommLogin(Method);
    CommLogin(QByteArray&);
    const QByteArray    getPacket();

    //! type of authentification packet
    Method              method;
    //! user login
    QString             login;
    //! binary hash of the password
    QByteArray          sha1Pass;
    //! duration of the session send (in second)
    quint32             sessionTime;
    //! binary of the session string
    QByteArray          sessionString;

private:
    void                read(QByteArray&);
    void                write(QByteArray&);
};

QDebug operator<<(QDebug, CommLogin&);

#endif // COMMLOGIN_H
