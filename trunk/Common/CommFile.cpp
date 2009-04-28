#include "CommFile.h"

CommFile::CommFile() : CommPacket(CommPacket::FILE)
{
}

CommFile::CommFile(QByteArray& a) : CommPacket(CommPacket::FILE)
{
}

const QByteArray CommFile::getPacket()
{
    QByteArray a = CommPacket::getPacket();
    return a;
}

QDebug operator<<(QDebug d, CommFile& f)
{
    return d;
}
