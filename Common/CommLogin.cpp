#include "CommLogin.h"
#include <QDateTime>
#include <QtEndian>
#include <QVariant>
#include <QDataStream>

#ifdef HORUS_CLIENT
#include "../Client/PluginManagerClient.h"
#include "../Client/MetaManager.h"
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
        stream >> serverDateTime;
        stream >> sessionEnd;
        stream >> sessionString;

#ifdef HORUS_CLIENT
        UserDataPlugin* plugin = MetaManager::getInstance()->findManager<PluginManager *>()->findPlugin<UserDataPlugin*>();
        if ( ! plugin)
            return;

        user = (UserData*)(plugin->getDataWithKey(stream));
        user->dataFromStream(stream);
                //MetaManager::getInstance()->findManager<PluginManagerClient *>()->setCurrentUser(user);
		// Why the previous line of code doesn't compile but with PluginManager compile ???
		((PluginManagerClient *)MetaManager::getInstance()->findManager<PluginManager *>())->setCurrentUser(user);
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
        stream << serverDateTime;
        stream << sessionEnd;
        stream << sessionString;
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
