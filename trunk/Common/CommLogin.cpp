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
#include "CommLogin.h"
#include <QDateTime>
#include <QtEndian>
#include <QVariant>
#include <QDataStream>

#ifdef HORUS_CLIENT
#include "../Client/PluginManagerClient.h"
#endif

#include "../Common/UserData.h"
#include "../Common/UserDataPlugin.h"

CommLogin::CommLogin(Method t) : CommPacket(CommPacket::LOGIN)
{
    method  = t;
}

CommLogin::CommLogin(const QByteArray& a) : CommPacket(CommPacket::LOGIN)
{
    method  = UNDEFINED;
    read(a);
}

const QByteArray CommLogin::getPacket() const
{
    QByteArray a;
    CommPacket::write(a);
    write(a);
    return a;
}

void CommLogin::read(const QByteArray& a)
{
    QDataStream stream(a);
    stream.device()->seek( lenParent() );

    stream >> (quint8&)method;
    if (method >= __LAST__)
        method = UNDEFINED;

    if (method == LOGIN_PASSWORD || method == LOGIN_SESSION)
    {
        stream >> login;
        if (method == LOGIN_PASSWORD)
            stream >> password;
        else
            stream >> sessionString;
    }
    else if (method == ACCEPTED)
    {
		stream >> serverDateTime
			   >> sessionEnd
			   >> sessionString
			   >> nbrDataForUpdate;

#ifdef HORUS_CLIENT
		UserDataPlugin* plugin = PluginManagerClient::instance()->findPlugin<UserDataPlugin*>();
        if ( ! plugin)
            return;

		user = (UserData*)(plugin->dataWithKey(stream));
        user->dataFromStream(stream);
		login = user->login();
	}
	else if (method == DISCONNECTED)
	{
		qCritical() << QObject::tr("You have been disconnected from server, please reconnect.");
#endif
    }
}

void CommLogin::write(QByteArray& a) const
{
    QDataStream stream(&a, QIODevice::WriteOnly);
    stream.device()->seek( lenParent() );

    stream << (quint8)method;

    if (method == LOGIN_PASSWORD || method == LOGIN_SESSION)
    {
        stream << login;
        if (method == LOGIN_PASSWORD)
            stream << password;
        else
            stream << sessionString;
    }
    else if (method == ACCEPTED)
    {
		stream << serverDateTime
			   << sessionEnd
			   << sessionString
			   << nbrDataForUpdate;
        user->keyToStream(stream);
        user->dataToStream(stream);
    }
 }

QDebug operator<<(QDebug d, const CommLogin& cl)
{
    static const char*  typeMessages[] =
    {
        "Undefined    ",
        "Login Pass   ",
        "Login Session",
        "Logout       ",
        "Accepted     ",
        "Refused      ",
        "Disconnected "
    };

    d << (CommPacket&)cl
      << typeMessages[ cl.method ];

    if (cl.method == CommLogin::ACCEPTED)
        d << cl.sessionString.toHex()
          << cl.sessionEnd;

    else if (cl.method == CommLogin::LOGIN_PASSWORD)
        d << cl.login
          << cl.password.toHex();

    else if (cl.method == CommLogin::LOGIN_SESSION)
        d << cl.login
          << cl.sessionString.toHex();

    return d;
}
