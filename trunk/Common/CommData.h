#ifndef COMMDATA_H
#define COMMDATA_H

#include "CommPacket.h"

class CommData : public CommPacket
{
public:
    CommData(const QString& type);
    CommData(const QByteArray&);
    const QByteArray getPacket() const;

    //! error message transmitted too for precision
    QString          type;
    QByteArray       data;

private:
    void             read(const QByteArray&);
    void             write(QByteArray&) const;
};

#endif // COMMDATA_H
