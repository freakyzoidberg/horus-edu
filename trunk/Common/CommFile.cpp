#include "CommFile.h"

CommFile::CommFile() : CommPacket(CommPacket::FILE)
{
}

CommFile::CommFile(QByteArray& a) : CommPacket(CommPacket::FILE)
{
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
    quint8 t = a[0];
    if (t >= __LAST__)
        method = UNDEFINED;
    else
        method = (fType)t;
    a.remove(0,1);
}

void CommFile::write(QByteArray& a)
{
}

QDebug operator<<(QDebug d, CommFile& p)
{
    return d;
}
