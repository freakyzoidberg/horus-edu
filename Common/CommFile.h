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
                  LIST, DOWNLOAD, UPLOAD,
                  AUTHORIZED,
                  NOT_AUTHORIZED, NOT_FOUND,
                  __LAST__};

    CommFile();
    CommFile(QByteArray&);
    const QByteArray getPacket();

    Method      method;
    //! name of the file
    QString     file;
    //! first byte of the file to read/write
    quint64     from;
    //! length to read/write, 0 for everything until the end
    quint64     length;

    //! key to open the connexion to the new socket
    QByteArray  key;

    //! the node in the organizational tree for a LIST request
    quint32     id;
    //! list of files in the node for the LIST request
    QList<CommFileInfo> fileList;

private:
    void                read(QByteArray&);
    void                write(QByteArray&);
};

QDebug operator<<(QDebug, const CommFile&);

#endif // COMMFILE_H
