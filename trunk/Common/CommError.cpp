#include "CommError.h"

CommError::CommError(eType _type, const char* _errorMessage) : CommPacket(CommPacket::ERROR)
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

CommError::CommError(QByteArray& a) : CommPacket(CommPacket::ERROR)
{
    read(a);
}

const QByteArray CommError::getPacket()
{
    QByteArray a;
    CommPacket::write(a);
    write(a);
    return a;
}

void CommError::read(QByteArray& a)
{
    quint8 t = a[0];
    if (t >= __LAST__)
        errorType = UNDEFINED;
    else
        errorType = (eType)t;
    a.remove(0, 1);
    errorMessage = a;
}

void CommError::write(QByteArray& a)
{
    a.append(errorType);
    a.append(errorMessage);
}

QDebug operator<<(QDebug d, CommError& e)
{
    return d << (CommPacket&)e << e.errorType << e.errorMessage;
}
