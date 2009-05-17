#include "CommFileInfo.h"

QDataStream& operator>>(QDataStream& s, CommFileInfo& i)
{
    return s >> i.fileName
             >> i.size
             >> i.ctime
             >> i.mtime
             >> i.checksumSha1
             >> i.owner;
}

QDataStream& operator<<(QDataStream& s, const CommFileInfo& i)
{
    return s << i.fileName
             << i.size
             << i.ctime
             << i.mtime
             << i.checksumSha1
             << i.owner;
}

QDebug operator<<(QDebug d, const CommFileInfo& i)
{
    return d << i.fileName
             << i.size
             << i.ctime
             << i.mtime
             << i.checksumSha1
             << i.owner;
}
