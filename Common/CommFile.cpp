#include "CommFile.h"

CommFile::CommFile(Method _method, quint32 _id, QIODevice::OpenMode _mode) : CommPacket(CommPacket::FILE)
{
    method = _method;
    mode = _mode;
    id = _id;
    start = 0;
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

    quint8 m; stream >> m;
    if (m < __LAST__)
        method = (Method)m;
    else
        method = UNDEFINED;

    stream >> id
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
           << id
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

        "List Directory",
        "Read File",
        "Write File",
        "Delete file",

        "Directory content",
        "File content",
        "Transfert not allowed",
        "File not found",
        "File deleted"
    };

    d << (CommPacket&)p
      << methods[ p.method ]
      << p.id
      << p.start
      << p.fileInfo
      << p.key.toHex();

    foreach (const CommFileInfo pos, p.fileList)
        d << pos;

    return d;
}
