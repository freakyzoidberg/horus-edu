#include "CommConfig.h"

CommConfig::CommConfig() : CommPacket(CommPacket::CONFIG)
{
}

CommConfig::CommConfig(QByteArray& a) : CommPacket(CommPacket::CONFIG)
{
}

const QByteArray CommConfig::getPacket()
{
    QByteArray a = CommPacket::getPacket();
    return a;
}

QDebug operator<<(QDebug d, CommConfig& c)
{
    return d;
}
