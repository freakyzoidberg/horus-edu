#include "CommError.h"

const quint8 CommError::typeNumber = 4;
const char*  CommError::typeNames[] =
{
    "Unknow Error",
    "Connexion not initialized"
    "Connexion already initialized"
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

QDataStream& operator<<(QDataStream& ds, CommError& e)
{
    qDebug() << "[out]" << e;
    return ds << (CommPacket&)e << (quint8&)e.errorType << e.errorMessage;
}

QDataStream& operator>>(QDataStream& ds, CommError& e)
{
    ds >> (quint8&)e.errorType;
    if (e.errorType >= CommError::typeNumber)
        e.errorType  = CommError::UNKNOW;

    ds >> e.errorMessage;
    qDebug() << "[ in]" << e;
    return ds;
}

QDebug operator<<(QDebug d, CommError& e)
{
    return d << (CommPacket&)e << e.errorType << e.errorMessage;
}
