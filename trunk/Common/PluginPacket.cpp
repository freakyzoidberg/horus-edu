#include "PluginPacket.h"

QDebug& operator<<(QDebug& d, const PluginPacket& p)
{ return d
    << p.packetVersion
    << p.sourcePlugin
    << p.targetPlugin
    << p.request
    << p.error
    << p.errorMessage
; }

QDataStream& operator<<(QDataStream& d, const PluginPacket& p)
{ return d
    << p.packetVersion
    << p.sourcePlugin
    << p.targetPlugin
    << p.request
    << p.error
    << p.errorMessage
    << p.data
; }

QDataStream& operator>>(QDataStream& d, PluginPacket& p)
{ return d
    >> p.packetVersion
    >> p.sourcePlugin
    >> p.targetPlugin
    >> p.request
    >> p.error
    >> p.errorMessage
    >> p.data
; }
