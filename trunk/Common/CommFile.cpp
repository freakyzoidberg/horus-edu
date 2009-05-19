#include "CommFile.h"

CommFile::CommFile(Method _method, quint32 _id) : CommPacket(CommPacket::FILE)
{
    method = _method;
    id = _id;
    start = 0;
    key = "";
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
    QDataStream stream(&a, QIODevice::ReadOnly);

    quint8 m;
    stream >> m;
    method = UNDEFINED;
    if (m < __LAST__)
        method = (Method)m;

    stream >> id;

    if (method == READ_FILE || method == WRITE_FILE)
        stream >> start;

    else if (method == DIR)
        while ( ! stream.atEnd())
        {
            CommFileInfo i;
            stream >> i;
            fileList.append(i);
        }

    else if (method == FILE)
        stream >> fileInfo
               >> key;
}

void CommFile::write(QByteArray& a)
{
    QDataStream stream(&a, QIODevice::WriteOnly);
    stream.device()->seek(a.length());

    stream << (quint8)method
           << id;

    if (method == READ_FILE || method == WRITE_FILE)
        stream << start;

    else if (method == DIR)
        foreach (const CommFileInfo pos, fileList)
            stream << pos;

    else if (method == FILE)
        stream << fileInfo
               << key;
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

    d << methods[ p.method ]
      << p.id;

    if (p.method == CommFile::READ_FILE || p.method == CommFile::WRITE_FILE)
        d << p.start;

    else if (p.method == CommFile::DIR)
        foreach (const CommFileInfo pos, p.fileList)
            d << pos;

    else if (p.method == CommFile::FILE)
        d << p.fileInfo
          << p.key.toHex();

    return d;
}
