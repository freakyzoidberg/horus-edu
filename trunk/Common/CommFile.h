#ifndef COMMFILE_H
#define COMMFILE_H

#include <QDateTime>

#include "CommPacket.h"

class FileInfo
{
    //! name of the file
    QString     fileName;
    //! actual size of the file
    quint64     size;
    //! creation time
    QDateTime   ctime;
    //! last modification date
    QDateTime   mtime;
    //! sha1 checksum of the file
    QByteArray  checksumSha1;
    //! user id of the owner of the file
    quint32     owner;
};

class CommFile : public CommPacket
{
public:
    CommFile();
    CommFile(QByteArray&);

    enum fType { UNDEFINED,
                 LIST, DOWNLOAD, UPLOAD,
                 AUTHORIZED,
                 NOT_AUTHORIZED, NOT_FOUND//,...
             };

    const QByteArray getPacket();

    fType       method;
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
    QList<FileInfo> fileList;

private:
    void                read(QByteArray&);
    void                write(QByteArray&);
};

QDebug operator<<(QDebug, CommFile&);

#endif // COMMFILE_H
