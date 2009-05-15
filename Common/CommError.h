#ifndef COMMERROR_H
#define COMMERROR_H

#include "CommPacket.h"

//! Communication packet for errors
class CommError : public CommPacket
{
public:
    //! differents error codes
    /*!
     * UNDEFINED is used when the type is not set yet, and for invalid value
     * __LAST__ is usde to know if a value is valid. a valid value is always inferior to __LAST__. __LAST__ is never used as a value
     */
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

QDebug operator<<(QDebug, const CommError&);

#endif // COMMERROR_H
