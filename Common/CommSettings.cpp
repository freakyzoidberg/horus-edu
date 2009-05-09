#include <QByteArray>

#include "CommSettings.h"

CommSettings::CommSettings() : CommPacket(CommPacket::CONFIG)
{
}

CommSettings::CommSettings(QByteArray& a) : CommPacket(CommPacket::CONFIG)
{
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
    QDataStream stream(&a, QIODevice::ReadOnly);

    stream >> (quint8&)method
           >> module;

    if (method != GET && method != SET)
    {
        method = UNDEFINED;
        return;
    }

    while ( ! stream.atEnd())
    {
        QByteArray key;
        stream >> key
               >> settings[ key ];
    }
}

void CommSettings::write(QByteArray& a)
{
    QDataStream stream(&a, QIODevice::WriteOnly);
    stream.device()->seek(a.length());

    stream << (quint8&)method
           << module;

    QHash<QByteArray,QVariant>::const_iterator s = settings.begin();
    while (s != settings.end())
    {
        stream << s.key()
               << s.value();
    }
}

QDebug operator<<(QDebug d, CommSettings& p)
{
    return d << (CommPacket&)p
             << p.method
             << p.module
             << p.settings;
}
