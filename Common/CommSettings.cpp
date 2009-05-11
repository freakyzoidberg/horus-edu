#include <QByteArray>

#include "CommSettings.h"

CommSettings::CommSettings() : CommPacket(CommPacket::SETTINGS)
{
    method = UNDEFINED;
}

CommSettings::CommSettings(QByteArray& a) : CommPacket(CommPacket::SETTINGS)
{
    method = UNDEFINED;
    read(a);
}

const QByteArray CommSettings::getPacket()
{
    QByteArray a;
    CommPacket::write(a);
    write(a);
    return a;
}

void CommSettings::read(QByteArray& a)
{
    if ((char)a[0] < (char)__LAST__)
        method = (sType)(char)a[0];

    module = a.mid(2, a[1]);
    a.remove(0, a[1] + 2);

#ifdef HORUS_SERVER
    settings = a;
#else //HORUS_CLIENT
    QDataStream stream(&a, QIODevice::ReadOnly);
    stream >> settings;
#endif
}

void CommSettings::write(QByteArray& a)
{
    a.append(method);
    a.append(module.length());
    a.append(module);

#ifdef HORUS_SERVER
    a.append(settings);
#else //HORUS_CLIENT
    QDataStream stream(&a, QIODevice::WriteOnly);
    stream.device()->seek(a.length());
    stream << settings;
#endif
}

QDebug operator<<(QDebug d, CommSettings& p)
{
    return d << (CommPacket&)p
             << p.method
             << p.module
#ifdef HORUS_SERVER
             << p.settings.length()
             << p.settings.toHex();
#else //HORUS_CLIENT
             << p.settings;
#endif
}
