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
                  ACCESS_FILE, DELETE_FILE, STAT_FILE,
                  NODE_LIST, USER_LIST,
                  __LAST_METHOD__};
    enum Error { NO_ERROR, PERMITION_DENIED, NOT_FOUND, ALREADY_EXIST, __LAST_ERROR__ };


    CommFile(Method method=UNDEFINED, quint32 id=0, QIODevice::OpenMode mode=0);
    CommFile(QByteArray&);
    const QByteArray getPacket() const;

    //! type of request
    Method      method;
    //! type of error
    Error       error;

    //! first byte of the file to read or write (seek)
    /*! ACCESS_FILE */
    quint64     start;

    //! open mode : READ/WRITE/APPEND/TRUNCATE
    /*! ACCESS_FILE or DELETE_FILE or STAT_FILE */
    QIODevice::OpenMode mode;
    //! key to open the connexion to the new socket
    /*! ACCESS_FILE or DELETE_FILE or STAT_FILE */
    QByteArray  key;
    //! info of one file for the GET request
    /*! ACCESS_FILE or DELETE_FILE or STAT_FILE */
    CommFileInfo        fileInfo;

    //! list of files in the node for the LIST request
    /*! NODE_LIST or USER_LIST */
    QList<CommFileInfo> fileList;
    //! the node in the organizational tree for a LIST request or the id of file fot a GET
    /*! NODE_LIST */
    quint32     nodeId;

private:
    void                read(QByteArray&);
    void                write(QByteArray&) const;
};

QDebug operator<<(QDebug, const CommFile&);

#endif // COMMFILE_H
