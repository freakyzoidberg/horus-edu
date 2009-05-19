#include <QByteArray>

#include "CommSettings.h"

CommSettings::CommSettings() : CommPacket(CommPacket::SETTINGS)
{
    method = UNDEFINED;
    scope = CLIENT_USER_SCOPE;
}

CommSettings::CommSettings(QByteArray& a) : CommPacket(CommPacket::SETTINGS)
{
    method = UNDEFINED;
    scope = CLIENT_USER_SCOPE;
    read(a);
}

const QByteArray CommSettings::getPacket()
{
    QByteArray a;
    CommPacket::write(a);
    write(a);
    return a;
}

const QByteArray& CommSettings::getBinarySettings()
{
    return settings;
}

void CommSettings::setBinarySettings(const QByteArray& b)
{
    settings = b;
}

QVariant CommSettings::getVariantSettings()
{
    QVariant v;
    QDataStream stream(&settings, QIODevice::ReadOnly);
    stream >> v;
    return v;
}

void CommSettings::setVariantSettings(const QVariant& v)
{
    settings.clear();
    QDataStream stream(&settings, QIODevice::WriteOnly);
    stream << v;
}

void CommSettings::read(QByteArray& a)
{
    if ((char)a[0] < (char)__LAST__)
        method = (Method)(char)a[0];

    if (method == PERMISSION_DENIED)
        return;

    if ((char)a[1] < (char)__LAST_SCOPE__)
        scope = (Scope)(char)a[1];

    plugin = a.mid(3, a[2]);
    a.remove(0, 3 + a[2]);

    settings = a;
}

void CommSettings::write(QByteArray& a)
{
    a.append(method);
    if (method == PERMISSION_DENIED)
        return;

    a.append(scope);
    a.append(plugin.length());
    a.append(plugin);
    a.append(settings);
}

QDebug operator<<(QDebug d, const CommSettings& p)
{
    static const char*  methodNames[] =
    {
        "Undef ",
        "Get   ",
        "Set   ",
        "Value ",
        "Denied"
    };
    static const char*  scopeNames[] =
    {
        "Client-User  ",
        "Client-System",
        "Server-User  ",
        "Server-System"
    };

    return d << (CommPacket&)p
             << methodNames[ p.method ]
             << scopeNames[ p.scope ]
             << p.plugin;
//             << p.getBinarySettings().length();
}
