#ifndef COMMPACKET_H
#define COMMPACKET_H

#include <QDataStream>
#include <QObject>
#include <QDebug>

/*!
 * After authentification, each packets are transmited inside this container
 */
class CommPacket
{
  Q_ENUMS(msgType)
public:
    enum            msgType { UNKNOW_PROTOCOL, ALIVE, LOGIN, FILE, CONFIG, MODULE };

    CommPacket(msgType _type = UNKNOW_PROTOCOL);

    msgType         type;

    static const quint8         typeNumber;
    static const char*          typeMessages[];
};

QDataStream& operator<<(QDataStream&, CommPacket&);
QDataStream& operator>>(QDataStream&, CommPacket&);

QDebug operator<<(QDebug, CommPacket&);

#endif // COMMPACKET_H
