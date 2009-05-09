#ifndef COMMCONFIG_H
#define COMMCONFIG_H

#include <QHash>
#include <QVariant>

#include "CommPacket.h"

class CommSettings : public CommPacket
{
public:
    CommSettings();
    CommSettings(QByteArray&);

    enum sType { UNDEFINED, GET, SET };

    const QByteArray    getPacket();

    //! method GET or SET modules
    sType                       method;
    //! module name
    QByteArray                  module;
    //! Hash table containing all [ key ] = value for the settings of the module
    QHash<QByteArray, QVariant> settings;

private:
    void                read(QByteArray&);
    void                write(QByteArray&);
};

QDebug operator<<(QDebug, CommSettings&);

#endif // COMMCONFIG_H
