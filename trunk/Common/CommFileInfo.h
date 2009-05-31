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
    CommFileInfo();

    //! id of the file
    quint32     id;
    //! name of the file
    QString     fileName;
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

QDebug operator<<(QDebug, const CommFileInfo&);
QDataStream& operator>>(QDataStream&, CommFileInfo&);
QDataStream& operator<<(QDataStream&, const CommFileInfo&);

#endif // COMMFILEINFO_H
