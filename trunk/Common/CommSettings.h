#ifndef COMMCONFIG_H
#define COMMCONFIG_H

#include <QHash>

#include "CommPacket.h"

typedef QHash<QByteArray, QByteArray> Settings;

class CommSettings : public CommPacket
{
public:
    CommSettings();
    CommSettings(QByteArray&);
    const QByteArray getPacket();

    QHash<QByteArray, Settings> setings;
};

QDebug operator<<(QDebug, CommSettings&);

#endif // COMMCONFIG_H
