#ifndef COMMERROR_H
#define COMMERROR_H

#include "CommPacket.h"

class CommError : public CommPacket
{
public:
    //! differents error codes
    enum           Error { UNDEFINED, NOT_INITIALIZED, ALREADY_INITIALIZED, NOT_AUTHENTICATED, UNKNOWN_PROTO_VERSION, PROTOCOL_ERROR, __LAST__ };

    CommError(Error _type, const char* _error = 0);
    CommError(QByteArray&);
    const QByteArray getPacket();

    //! error code transmitted
    Error          errorType;
    //! error message transmitted too for precision
    QByteArray     errorMessage;

private:
    void           read(QByteArray&);
    void           write(QByteArray&);
};

QDebug operator<<(QDebug, CommError&);

#endif // COMMERROR_H
