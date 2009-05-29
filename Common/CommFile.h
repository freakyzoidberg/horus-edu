#ifndef COMMFILE_H
#define COMMFILE_H

#include "CommPacket.h"
#include "CommFileInfo.h"

//! Communication packet to ask for file transfert authorisation and file list
class CommFile : public CommPacket
{
public:
    /*!
     * UNDEFINED is used when the type is not set yet, and for invalid value
     * __LAST__ is usde to know if a value is valid. a valid value is always inferior to __LAST__. __LAST__ is never used as a value
     */
    enum Method { UNDEFINED,
                  CONTENT_REQUEST, DELETE_REQUEST, STAT_REQUEST,// client -> server
                  CONTENT,         DELETED,        STAT,        // server -> client
                  PERMITION_DENIED, NOT_FOUND,                       // errors server -> client
                  __LAST__};

    CommFile(Method method=UNDEFINED, quint32 id=0, QIODevice::OpenMode mode=0);
    CommFile(QByteArray&);
    const QByteArray getPacket() const;

    //! type of request
    Method      method;
    //! the node in the organizational tree for a LIST request or the id of file fot a GET
    quint32     id;

    //! first byte of the file to read or write (seek)
    /*! READ_FILE or WRITE_FILE */
    quint64     start;

    //! open mode : READ/WRITE/APPEND/TRUNCATE
    /*! FILE */
    QIODevice::OpenMode mode;
    //! key to open the connexion to the new socket
    /*! FILE */
    QByteArray  key;
    //! info of one file for the GET request
    /*! FILE */
    CommFileInfo        fileInfo;

    //! list of files in the node for the LIST request
    /*! DIRECTORY */
    QList<CommFileInfo> fileList;

private:
    void                read(QByteArray&);
    void                write(QByteArray&) const;
};

QDebug operator<<(QDebug, const CommFile&);

#endif // COMMFILE_H
