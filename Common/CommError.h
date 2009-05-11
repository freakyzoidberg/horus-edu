#ifndef COMMERROR_H
#define COMMERROR_H

#include "CommPacket.h"

class CommError : public CommPacket
{
public:
    enum                eType { UNDEFINED, NOT_INITIALIZED, ALREADY_INITIALIZED, NOT_AUTHENTICATED, UNKNOWN_PROTO_VERSION, PROTOCOL_ERROR, __LAST__ };
    CommError(eType _type, const char* _error = 0);
    CommError(QByteArray&);

    const QByteArray getPacket();

    eType          errorType;
    QByteArray     errorMessage;

private:
    void                read(QByteArray&);
    void                write(QByteArray&);
};

QDebug operator<<(QDebug, CommError&);

#endif // COMMERROR_H
