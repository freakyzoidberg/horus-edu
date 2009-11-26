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
