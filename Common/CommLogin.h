#ifndef COMMLOGIN_H
#define COMMLOGIN_H

#include <QDataStream>
#include <QObject>

#include "Defines.h"
#include "CommMiniString.h"

/*!
 * Response from the client to the server
 * after the first "ConnexionMessage" from the server
 */
class CommLogin
{
  Q_ENUMS(packetType)
//  Q_ENUMS(authType)

public:
    /*!
     * Type of authenfication
     * in the future we may want to add the certificate auth. or something else
     */
    enum            packetType{ ERROR, LOGIN , LOGOUT , ACCEPTED , REFUSED };
//    enum            authType { HASH_MD5, SESSION };//...

    CommLogin(packetType _type = ERROR, CommMiniString _login = "");

    packetType      type;
    CommMiniString  login;
//    authType        aType;
    static const quint8         typeNumber;
    static const char*          typeMessages[];
};

QDataStream& operator<<(QDataStream&, CommLogin&);
QDataStream& operator>>(QDataStream&, CommLogin&);

QDebug operator<<(QDebug, CommLogin&);

#endif // COMMLOGIN_H
