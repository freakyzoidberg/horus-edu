#ifndef COMMLOGIN_H
#define COMMLOGIN_H

#include <QDataStream>
#include <QObject>

#include "CommMiniString.h"

/*!
 * Response from the client to the server
 * after the first "ConnexionMessage" from the server
 */
class CommLogin
{
  Q_ENUMS(authType)

public:
    /*!
     * Type of authenfication
     * in the future we may want to add the ssl certificate for auth. or something else
     */
    enum            authType { HASH_MD5 };

    CommLogin(CommMiniString clientVersion = "", CommMiniString _login = "", authType _type = HASH_MD5);

    /*!
     * Send the version of the client if there is some change in the protocol in the future
     */
    CommMiniString  clientVersion;
    CommMiniString  login;
    authType        type;
};

QDataStream& operator<<(QDataStream&, CommLogin&);
QDataStream& operator>>(QDataStream&, CommLogin&);

#endif // COMMLOGIN_H
