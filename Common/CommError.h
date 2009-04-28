#ifndef COMMERROR_H
#define COMMERROR_H

#include "CommPacket.h"

class CommError : public CommPacket
{
public:
    enum                eType { UNKNOW, NOT_INITIALIZED, ALREADY_INITIALIZED, NOT_AUTHENTICATED, UNKNOWN_PROTO_VERSION };
    CommError(eType _type, const char* _error = 0);
    CommError(QByteArray&);
    const QByteArray getPacket();

    quint8         errorType;
    QByteArray     errorMessage;

    static const quint8 typeNumber;
    static const char*  typeNames[];
};

QDebug operator<<(QDebug, CommError&);

#endif // COMMERROR_H
