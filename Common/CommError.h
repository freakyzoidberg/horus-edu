#ifndef COMMERROR_H
#define COMMERROR_H

#include "CommPacket.h"
#include "CommMiniString.h"

class CommError : public CommPacket
{
public:
    enum                eType { UNKNOW, NOT_INITIALIZED, ALREADY_INITIALIZED, UNKNOWN_PROTO_VERSION };
    CommError(eType _type = UNKNOW, const char* _error = "");

    eType          errorType;
    CommMiniString errorMessage;

    static const quint8 typeNumber;
    static const char*  typeNames[];
};

QDataStream& operator<<(QDataStream&, CommError&);
QDataStream& operator>>(QDataStream&, CommError&);

QDebug operator<<(QDebug, CommError&);

#endif // COMMERROR_H
