#ifndef COMMFILEINFO_H
#define COMMFILEINFO_H

#include <QDataStream>
#include <QDebug>
#include <QString>
#include <QByteArray>
#include <QDateTime>

//! Communication packet for CommFile::LIST. Contain a description of one file
class CommFileInfo
{
public:
    inline CommFileInfo() { id = 0; fileName = ""; size = 0; ownerId = 0; nodeId = 0; }

    //! id of the file
    quint32     id;
    //! name of the file
    QString     fileName;
    //! mime-type of the file
    QString     mimeType;
    //! actual size of the file
    quint64     size;
    //! creation time
    QDateTime   ctime;
    //! last modification date
    QDateTime   mtime;
    //! checksum sha1 of the file
    QByteArray  hashSha1;
    //! id of the owner
    quint32     ownerId;
    //! id of the parent node
    quint32     nodeId;
};

inline bool   operator==(const CommFileInfo& a, const CommFileInfo& b) { return (
    a.id       == b.id &&
    a.fileName == b.fileName &&
    a.mimeType == b.mimeType &&
    a.mtime    == b.mtime &&
    a.hashSha1 == b.hashSha1 &&
    a.ownerId  == b.ownerId &&
    a.nodeId   == b.nodeId
); }

inline bool   operator!=(const CommFileInfo& a, const CommFileInfo& b) { return ( ! (a == b)); }

inline QDebug operator<<(QDebug d, const CommFileInfo& i) { return d
    << i.id
    << i.fileName
    << i.mimeType
    << i.size
    << i.ctime
    << i.mtime
    << i.hashSha1.toHex()
    << i.ownerId
    << i.nodeId
; }

inline QDataStream& operator>>(QDataStream& s, CommFileInfo& i) { return s
    >> i.id
    >> i.fileName
    >> i.mimeType
    >> i.size
    >> i.ctime
    >> i.mtime
    >> i.hashSha1
    >> i.ownerId
    >> i.nodeId
; }

inline QDataStream& operator<<(QDataStream& s, const CommFileInfo& i) { return s
    << i.id
    << i.fileName
    << i.mimeType
    << i.size
    << i.ctime
    << i.mtime
    << i.hashSha1
    << i.ownerId
    << i.nodeId
; }

#endif // COMMFILEINFO_H
