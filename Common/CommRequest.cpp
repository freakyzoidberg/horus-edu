#include "CommRequest.h"

CommRequest::CommRequest()
{
    idPacket = 0;
    type = ALIVE;
}

QDataStream& operator<<(QDataStream& ds, CommRequest& cr)
{
    ds << cr.idPacket;
    ds << (quint8&)cr.type;
    return ds;
}

QDataStream& operator>>(QDataStream& ds, CommRequest& cr)
{
    ds >> cr.idPacket;
    ds >> (quint8&)cr.type;
    return ds;
}
