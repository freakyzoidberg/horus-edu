#include "CommData.h"

CommData::CommData(const QString& _type) : CommPacket(CommPacket::DATA)
{
    type = _type;
}

CommData::CommData(const QByteArray& a) : CommPacket(CommPacket::DATA)
{
    read(a);
}

const QByteArray CommData::getPacket() const
{
    QByteArray a;
    CommPacket::write(a);
    write(a);
    return a;
}

void CommData::read(const QByteArray& a)
{
    type = a.mid(1, a[0]);
    data = a.mid(1 + a[0]);
}

void CommData::write(QByteArray& a) const
{
    a.append((char)type.length());
    a.append(type);
    a.append(data);
}

QDebug operator<<(QDebug d, const CommData& e)
{
    return d << (CommPacket&)e << e.type << e.data;
}
