#ifndef COMMCONFIG_H
#define COMMCONFIG_H

#include "CommPacket.h"

class CommConfig : public CommPacket
{
public:
    CommConfig();
    CommConfig(QByteArray&);
    const QByteArray getPacket();
};

QDebug operator<<(QDebug, CommConfig&);

#endif // COMMCONFIG_H
