#include "CommError.h"

const quint8 CommError::typeNumber = 5;
const char*  CommError::typeNames[] =
{
    "Unknow Error",
    "Connexion not initialized"
    "Connexion already initialized"
    "Not authenticated"
    "Unknown protocol version"
};

CommError::CommError(eType _type, const char* _errorMessage) : CommPacket(CommPacket::ERROR)
{
    errorType = _type;
    if ( ! _errorMessage || ! _errorMessage[0])
        errorMessage = CommError::typeNames[ errorType ];
    else
        errorMessage = _errorMessage;
}

CommError::CommError(QByteArray& a) : CommPacket(CommPacket::ERROR)
{
    errorType = a[0];
    if (errorType > typeNumber)
        errorType = UNKNOW;
    a.remove(0, 1);
    errorMessage = a;
}

const QByteArray CommError::getPacket()
{
    QByteArray a = CommPacket::getPacket();
    a.append(errorType);
    a.append(errorMessage);
    return a;
}

QDebug operator<<(QDebug d, CommError& e)
{
    return d << (CommPacket&)e << e.errorType << e.errorMessage;
}
