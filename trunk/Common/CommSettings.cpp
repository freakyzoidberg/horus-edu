#include "CommSettings.h"

CommSettings::CommSettings() : CommPacket(CommPacket::CONFIG)
{
}

CommSettings::CommSettings(QByteArray& a) : CommPacket(CommPacket::CONFIG)
{
}

const QByteArray CommSettings::getPacket()
{
    QByteArray a = CommPacket::getPacket();
    return a;
}

QDebug operator<<(QDebug d, CommSettings& c)
{
    return d;
}
