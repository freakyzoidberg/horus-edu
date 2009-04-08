#include "CommError.h"

CommError::CommError(const char* _error) : CommPacket(CommPacket::ERROR)
{
    error = _error;
}

QDataStream& operator<<(QDataStream& ds, CommError& e)
{
    qDebug() << "[out]" << e;
    return ds << (CommPacket&)e << e.error;
}

QDataStream& operator>>(QDataStream& ds, CommError& e)
{
    qDebug() << "[ in]" << e;
    return ds >> e.error;
}

QDebug operator<<(QDebug d, CommError& e)
{
    return d << (CommPacket&)e << e.error;
}
