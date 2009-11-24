#include "CommData.h"
#include "Data.h"
#include <QObject>

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
    int len = lenParent();
    type = a.mid(len + 1,  a[ len ]);
    data = a.mid(len + 1 + a[ len ]);
}

void CommData::write(QByteArray& a) const
{
    a.append((char)type.length());
    a.append(type);
    a.append(data);
}

QDebug operator<<(QDebug d, const CommData& p)
{
	QDataStream stream(p.data);
	quint8 status;
	stream >> status;

	d << (CommPacket&)p << p.type << (Data::Status)status;
	if (status == Data::DATA_ERROR)
	{
		quint8 error;
		stream >> error;
		d << (Data::Error)error;
	}
	return d;
}
