#include "CommError.h"

CommError::CommError(Error _type, const char* _errorMessage) : CommPacket(CommPacket::ERROR)
{
    static const char*  typeNames[] =
    {
        "Unknow Error",
        "Connexion not initialized",
        "Connexion already initialized",
        "Not authenticated",
        "Unknown protocol version",
        "Protocol Error"
    };

    errorType = _type;
    if ( ! _errorMessage || ! _errorMessage[0])
        errorMessage = typeNames[ errorType ];
    else
        errorMessage = _errorMessage;
}

CommError::CommError(const QByteArray& a) : CommPacket(CommPacket::ERROR)
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
