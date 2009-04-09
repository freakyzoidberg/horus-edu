#include "CommError.h"

CommError::CommError(eType _type, const char* _errorMessage) : CommPacket(CommPacket::ERROR)
{
    errorType = _type;
    errorMessage = _errorMessage;
}

QDataStream& operator<<(QDataStream& ds, CommError& e)
{
    qDebug() << "[out]" << e;
    return ds << (CommPacket&)e << (quint8&)e.errorType << e.errorMessage;
}

QDataStream& operator>>(QDataStream& ds, CommError& e)
{
    qDebug() << "[ in]" << e;
    return ds >> (quint8&)e.errorType >> e.errorMessage;
}

QDebug operator<<(QDebug d, CommError& e)
{
    return d << (CommPacket&)e << e.errorType << e.errorMessage;
}
