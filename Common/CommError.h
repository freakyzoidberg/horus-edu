#ifndef COMMERROR_H
#define COMMERROR_H

#include "CommPacket.h"
#include "CommMiniString.h"

class CommError : public CommPacket
{
public:
    CommError(const char* _error = "");

    CommMiniString error;
};

QDataStream& operator<<(QDataStream&, CommError&);
QDataStream& operator>>(QDataStream&, CommError&);

QDebug operator<<(QDebug, CommError&);

#endif // COMMERROR_H
