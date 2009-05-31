#include "CommFileInfo.h"

CommFileInfo::CommFileInfo()
{
    id = 0;
    fileName = "";
    size = 0;
    ownerId = 0;
    nodeId = 0;
}

QDataStream& operator>>(QDataStream& s, CommFileInfo& i)
{
    return s >> i.id
             >> i.fileName
             >> i.size
             >> i.ctime
             >> i.mtime
             >> i.hashSha1
             >> i.ownerId
             >> i.nodeId;
}

QDataStream& operator<<(QDataStream& s, const CommFileInfo& i)
{
    return s << i.id
             << i.fileName
             << i.size
             << i.ctime
             << i.mtime
             << i.hashSha1
             << i.ownerId
             << i.nodeId;
}

QDebug operator<<(QDebug d, const CommFileInfo& i)
{
    return d << i.id
             << i.fileName
             << i.size
             << i.ctime
             << i.mtime
             << i.hashSha1.toHex()
             << i.ownerId
             << i.nodeId;
}
