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

QDebug operator<<(QDebug, const CommFileInfo&);
QDataStream& operator>>(QDataStream&, CommFileInfo&);
QDataStream& operator<<(QDataStream&, const CommFileInfo&);

#endif // COMMFILEINFO_H
