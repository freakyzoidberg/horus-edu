#ifndef EVENTDATAPLUGIN_H
#define EVENTDATAPLUGIN_H

#include "DataPlugin.h"

class TreeData;
class EventData;
class EventDataPlugin : public DataPlugin
{
    Q_OBJECT
#ifdef HORUS_SERVER
    Q_INTERFACES(ServerDataPlugin)
#endif
#ifdef HORUS_CLIENT
    Q_INTERFACES(ClientDataPlugin)
#endif

public:
	virtual EventData* getEvent(quint32 nodeId) = 0;
	virtual EventData* getEvent(TreeData* node) = 0;
};

#ifdef HORUS_SERVER
typedef EventDataPlugin ServerEventDataPlugin;
Q_DECLARE_INTERFACE(ServerEventDataPlugin, "net.horus.ServerEventDataPlugin/1.0");
#endif
#ifdef HORUS_CLIENT
typedef EventDataPlugin ClientEventDataPlugin;
Q_DECLARE_INTERFACE(ClientEventDataPlugin, "net.horus.ClientEventDataPlugin/1.0");
#endif

#endif // EVENTDATAPLUGIN_H
