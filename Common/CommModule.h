#ifndef COMMMODULE_H
#define COMMMODULE_H

#include "CommPacket.h"

/*!
 * If the "messageType" of the "CommunicationContainer" is "MODULE_COMM"
 * there is this class inside "content".
 * it's for the comunication between a module client and a module server
 */
class CommModule : public CommPacket
{
public:
    CommModule();
    CommModule(const char* src, const char* srcVer, const char* dest);

    CommMiniString  moduleSource;
    CommMiniString  moduleSourceVersion;
    CommMiniString  moduleDestination;
};

QDataStream& operator<<(QDataStream&, CommModule&);
QDataStream& operator>>(QDataStream&, CommModule&);

QDebug operator<<(QDebug, CommModule&);

#endif // COMMMODULE_H
