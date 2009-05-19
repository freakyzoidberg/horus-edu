#ifndef COMMLOGIN_H
#define COMMLOGIN_H

#include "CommPacket.h"

/*!
 * Response from the client to the server
 * after the first "ConnexionMessage" from the server
 */
//! Communication packet for login/logout/session
class CommLogin : public CommPacket
{
public:
    //! type of authentification packet
    /*!
     * Type of authenfication
     * in the future we may want to add the certificate auth. or something else
     *
     * UNDEFINED is used when the type is not set yet, and for invalid value
     * __LAST__ is usde to know if a value is valid. a valid value is always inferior to __LAST__. __LAST__ is never used as a value
     */
    enum                Method { UNDEFINED,
                                 LOGIN_PASSWORD, LOGIN_SESSION, LOGOUT, //CLIENT  -> SERVER
                                 ACCEPTED, REFUSED,                     // SERVER -> CLIENT
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

QDebug operator<<(QDebug, const CommLogin&);

#endif // COMMLOGIN_H
