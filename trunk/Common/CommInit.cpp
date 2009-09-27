#include "CommInit.h"

#include <QObject>

CommInit::CommInit(quint8 _protoVersion, const char* _fromName) : CommPacket(CommPacket::INIT)
{
    protoVersion = _protoVersion;
    fromName  = _fromName;
}

CommInit::CommInit(const QByteArray& a) : CommPacket(CommPacket::INIT)
{
    read(a);
}

const QByteArray CommInit::getPacket() const
{
    QByteArray a;
    CommPacket::write(a);
    write(a);
    return a;
}

void CommInit::read(const QByteArray& a)
{
    int len = lenParent();
    protoVersion = a[ len ];
    fromName = a.mid(len + 1);
}

void CommInit::write(QByteArray& a) const
{
    a.append(protoVersion);
    a.append(fromName);
}

QDebug operator<<(QDebug d, const CommInit& ci)
{
    return d << (CommPacket&)ci
		<< QObject::tr("proto v:") << ci.protoVersion
             << QObject::tr(" from:")    << ci.fromName;
}
