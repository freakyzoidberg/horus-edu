#include "CommFile.h"

CommFile::CommFile(Method _method, quint32 _id, QIODevice::OpenMode _mode) : CommPacket(CommPacket::FILE)
{
    method = _method;
    error = NO_ERROR;
    nodeId = _id;
    start = 0;
    mode = _mode;
    key = "";
}

CommFile::CommFile(QByteArray& a) : CommPacket(CommPacket::FILE)
{
    read(a);
}

const QByteArray CommFile::getPacket() const
{
    QByteArray a;
    CommPacket::write(a);
    write(a);
    return a;
}

void CommFile::read(QByteArray& a)
{
    QDataStream stream(a);

    quint8 tmp; stream >> tmp;
    if (tmp < __LAST_METHOD__)
        method = (Method)tmp;
    else
        method = UNDEFINED;

    stream >> tmp;
    if (tmp < __LAST_ERROR__)
        error = (Error)tmp;
    else
        error = NO_ERROR;

    stream >> nodeId
           >> start
           >> (quint8&)mode
           >> fileInfo
           >> key;

    //Filter only these modes
    mode &= QIODevice::ReadOnly|QIODevice::WriteOnly|QIODevice::Append|QIODevice::Truncate;

    while ( ! stream.atEnd())
    {
        CommFileInfo i;
        stream >> i;
        fileList.append(i);
    }
}

void CommFile::write(QByteArray& a) const
{
    QDataStream stream(&a, QIODevice::WriteOnly);
    stream.device()->seek(a.length());

    stream << (quint8)method
           << (quint8)error
           << nodeId
           << start
           << (quint8)mode
           << fileInfo
           << key;
    foreach (const CommFileInfo pos, fileList)
        stream << pos;
}

QDebug operator<<(QDebug d, const CommFile& p)
{
    static const char* methods[] =
    {
        "Undefined",
        "Access File",
        "New File",
        "Delete File",
        "Stat file",

        "Node List",
        "User List",
    };
    static const char* errors[] =
    {
        "No error",
        "Permition Denied",
        "File or node not found"
        "File already exist"
    };

    d << (CommPacket&)p
      << methods[ p.method ]
      << errors[ p.error ]
      << p.nodeId
      << p.start
      << p.mode
      << p.fileInfo
      << p.key.toHex();

    foreach (const CommFileInfo pos, p.fileList)
        d << pos;

    return d;
}
