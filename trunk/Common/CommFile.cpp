#include "CommFile.h"

CommFile::CommFile() : CommPacket(CommPacket::FILE)
{
    method = UNDEFINED;
}

CommFile::CommFile(QByteArray& a) : CommPacket(CommPacket::FILE)
{
    method = UNDEFINED;
    read(a);
}

const QByteArray CommFile::getPacket()
{
    QByteArray a;
    CommPacket::write(a);
    write(a);
    return a;
}

void CommFile::read(QByteArray& a)
{
    if ((char)a[0] < (char)__LAST__)
        method = (Method)(char)a[0];
    a.remove(0,1);
}

void CommFile::write(QByteArray& a)
{
}

QDebug operator<<(QDebug d, CommFile& p)
{
    return d;
}
