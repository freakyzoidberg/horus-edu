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

QByteArray CommSettings::getBinarySettings(void)
{
    return settings;
}

void CommSettings::setBinarySettings(const QByteArray& b)
{
    settings = b;
}

QVariant CommSettings::getVariantSettings(void)
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

QDebug operator<<(QDebug d, CommSettings& p)
{
    static const char*  methodNames[] =
    {
        "Undefined",
        "Get",
        "Set",
        "Value",
        "Denied"
    };
    static const char*  scopeNames[] =
    {
        "Client-User Scope",
        "Client-System_Scope",
        "Server-User Scope",
        "Server-System Scope"
    };

    return d << (CommPacket&)p
             << methodNames[ p.method ]
             << scopeNames[ p.scope ]
             << p.plugin;
}
