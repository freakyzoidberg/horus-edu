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

    enum sType { UNDEFINED, GET, SET, RESPONSE, __LAST__ };

    const QByteArray    getPacket();

    //! method GET or SET modules
    sType                       method;
    //! module name
    QByteArray                  module;

#ifdef HORUS_SERVER
    //! Binary containig the QHash of the client but not parsed onto the server
    QByteArray settings;
#else //HORUS_CLIENT
    //! Hash table containing all [ key ] = value for the settings of the module
    QVariant   settings;
#endif

private:
    void                read(QByteArray&);
    void                write(QByteArray&);
};

QDebug operator<<(QDebug, CommSettings&);

#endif // COMMCONFIG_H
