#ifndef COMMFILE_H
#define COMMFILE_H

#include "CommPacket.h"

class CommFile : public CommPacket
{
public:
    CommFile();
    CommFile(QByteArray&);
    const QByteArray getPacket();

    QString     dir;
    QString     file;
    quint64     from;
    quint64     length;
    QByteArray  key;
};

QDebug operator<<(QDebug, CommFile&);

#endif // COMMFILE_H
