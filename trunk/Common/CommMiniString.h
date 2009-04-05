#ifndef COMMMINISTRING_H
#define COMMMINISTRING_H

#include <QByteArray>
#include <QDataStream>

/*!
 * Same as a QByteArray (a classic String) but with a max length of 255 chars.
 * with this limit, this object can go in a a QDataStream with a uint8 for the length and not a uint32
 */
class CommMiniString : public QByteArray
{
public:
    CommMiniString(QByteArray&);
    CommMiniString(const char*);
    CommMiniString();
};

QDataStream& operator<<(QDataStream& ds, CommMiniString& cms);
QDataStream& operator>>(QDataStream& ds, CommMiniString& cms);

#endif // COMMMINISTRING_H
