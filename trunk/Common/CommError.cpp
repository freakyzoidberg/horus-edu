#include <QObject>

#include "CommError.h"

CommError::CommError(Error _type, const char* _errorMessage) : CommPacket(CommPacket::PACKET_ERROR)
{
    static const QString  typeNames[] =
    {
		QObject::tr("Unknow Error"),
        QObject::tr("Connexion not initialized"),
        QObject::tr("Connexion already initialized"),
        QObject::tr("Not authenticated"),
        QObject::tr("Unknown protocol version"),
        QObject::tr("Protocol Error"),
        QObject::tr("Internal Error")
    };

    errorType = _type;
    if ( ! _errorMessage || ! _errorMessage[0])
        errorMessage = qPrintable(typeNames[ errorType ]);
    else
        errorMessage = _errorMessage;
}

CommError::CommError(const QByteArray& a) : CommPacket(CommPacket::PACKET_ERROR)
{
    errorType = UNDEFINED;
    read(a);
}

const QByteArray CommError::getPacket() const
{
    QByteArray a;
    CommPacket::write(a);
    write(a);
    return a;
}

void CommError::read(const QByteArray& a)
{
    int len = lenParent();
    if ((char)a[ len ] < (char)__LAST__)
        errorType = (Error)(char)a[ len ];
    errorMessage = a.mid(len + 1);
}

void CommError::write(QByteArray& a) const
{
    a.append(errorType);
    a.append(errorMessage);
}

QDebug operator<<(QDebug d, const CommError& e)
{
    return d << (CommPacket&)e << e.errorType << e.errorMessage;
}
