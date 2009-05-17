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
                  LIST_DIR, READ_FILE, WRITE_FILE, DELETE_FILE, // CLIENT -> SERVER
                  DIR, FILE, NOT_ALLOWED, NOT_FOUND, DELETED,   // SERVER -> CLIENT
                  __LAST__};

    CommFile(Method method=UNDEFINED, quint32 id=0);
    CommFile(QByteArray&);
    const QByteArray getPacket();

    //! type of request
    Method      method;
    //! the node in the organizational tree for a LIST request or the id of file fot a GET
    quint32     id;

    //! first byte of the file to read or write (seek)
    /*! READ_FILE or WRITE_FILE */
    quint64     start;

    //! key to open the connexion to the new socket
    /*! FILE */
    QByteArray  key;
    //! info of one file for the GET request
    /*! FILE */
    CommFileInfo        fileInfo;

    //! list of files in the node for the LIST request
    /*! DIR */
    QList<CommFileInfo> fileList;

private:
    void                read(QByteArray&);
    void                write(QByteArray&);
};

QDebug operator<<(QDebug, const CommFile&);

#endif // COMMFILE_H
