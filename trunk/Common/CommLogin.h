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
                               ACCEPTED, REFUSED };                            // SERVER -> CLIENT

    CommLogin(lType);
    CommLogin(QByteArray&);
    const QByteArray getPacket();

    quint8       loginType;
    QString      login;
    QByteArray   sha1Pass;
    quint16      sessionTime;
    QByteArray   sessionString;

    static const quint8 typeNumber;
    static const char*  typeMessages[];
};

QDebug operator<<(QDebug, CommLogin&);

#endif // COMMLOGIN_H
