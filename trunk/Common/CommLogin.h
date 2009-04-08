#ifndef COMMLOGIN_H
#define COMMLOGIN_H

#include "CommPacket.h"

#include <QObject>

/*!
 * Response from the client to the server
 * after the first "ConnexionMessage" from the server
 */
class CommLogin : public CommPacket
{
  Q_ENUMS(lType)

public:
    /*!
     * Type of authenfication
     * in the future we may want to add the certificate auth. or something else
     */
    enum                lType{ UNDEFINED,
                               LOGIN_PASSWORD, LOGIN_SESSION, LOGOUT, //CLIENT  -> SERVER
                               ACCEPTED, REFUSED };                   // SERVER -> CLIENT

    CommLogin();

    lType               loginType;
    CommMiniString      login;
    CommMiniString      sha1Pass;
    CommMiniString      sessionString;
    quint32             sessionTime;

    static const quint8 typeNumber;
    static const char*  typeMessages[];

    bool isValidContent();
};

QDataStream& operator<<(QDataStream&, CommLogin&);
QDataStream& operator>>(QDataStream&, CommLogin&);

QDebug operator<<(QDebug, CommLogin&);

#endif // COMMLOGIN_H
