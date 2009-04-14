#ifndef COMMMODULE_H
#define COMMMODULE_H

#include <QByteArray>

#include "CommPacket.h"

/*!
 * If the "messageType" of the "CommunicationContainer" is "MODULE_COMM"
 * there is this class inside "content".
 * it's for the comunication between a module client and a module server
 */
class CommModule : public CommPacket
{
public:
    CommModule(QByteArray&);
    CommModule(const char* src, const char* srcVer, const char* dest, const QByteArray& data);
    QByteArray      getPacket();

    QByteArray  moduleSource;
    QByteArray  moduleSourceVersion;
    QByteArray  moduleDestination;
    QByteArray  moduleData;
};

QDebug operator<<(QDebug, CommModule&);

#endif // COMMMODULE_H
