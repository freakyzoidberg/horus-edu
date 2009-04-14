#ifndef COMMERROR_H
#define COMMERROR_H

#include "CommPacket.h"

class CommError : public CommPacket
{
public:
    enum                eType { UNKNOW, NOT_INITIALIZED, ALREADY_INITIALIZED, UNKNOWN_PROTO_VERSION };
    CommError(eType _type, const char* _error = 0);
    CommError(QByteArray&);
    QByteArray getPacket();

    quint8         errorType;
    QByteArray     errorMessage;

    static const quint8 typeNumber;
    static const char*  typeNames[];
};

//QDataStream& operator<<(QDataStream&, CommError&);
//QDataStream& operator>>(QDataStream&, CommError&);

QDebug operator<<(QDebug, CommError&);

#endif // COMMERROR_H
