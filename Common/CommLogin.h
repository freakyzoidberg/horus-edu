#ifndef COMMLOGIN_H
#define COMMLOGIN_H

#include <QDateTime>

#include "CommPacket.h"
class UserData;

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
                                 LOGIN_PASSWORD, LOGIN_SESSION, LOGOUT, //REQUEST
								 ACCEPTED, REFUSED, DISCONNECTED,     // RESPONSES
                                 __LAST__ };

    CommLogin(Method);
    CommLogin(const QByteArray&);
    const QByteArray    getPacket() const;

    //! type of authentification packet
    Method              method;

    // REQUEST
    //! user login
    QString             login;
    //! binary hash of the password
    QByteArray          password;

    // RESPONSE = ACCEPT
    //! duration of the session send (in second)
    QDateTime           serverDateTime;
    //! duration of the session send (in second)
    QDateTime           sessionEnd;
    //! binary of the session string
    QByteArray          sessionString;
    //! the information of the user
    UserData*           user;
	//! the number of data the user have to wait
	quint32				nbrDataForUpdate;

private:
    void                read(const QByteArray&);
    void                write(QByteArray&) const;
};

QDebug operator<<(QDebug, const CommLogin&);

#endif // COMMLOGIN_H
