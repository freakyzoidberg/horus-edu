#ifndef EVENTDATA_H
#define EVENTDATA_H

#include "Data.h"
#include "EventDataPlugin.h"

class EventData : public Data
{
	Q_OBJECT
#ifdef HORUS_SERVER
	Q_INTERFACES(ServerData)
#endif
#ifdef HORUS_CLIENT
	Q_INTERFACES(ClientData)
#endif

public:
	virtual QDateTime		startTime() const = 0;
	virtual void			setStartTime(const QDateTime& time) = 0;
	virtual QDateTime		endTime() const = 0;
	virtual void			setEndTime(const QDateTime& time) = 0;
	virtual TreeData*		node() const = 0;

protected:
	inline					EventData(EventDataPlugin* plugin) : Data(plugin) { }
	virtual inline			~EventData() {}
};

#ifdef HORUS_SERVER
typedef EventData ServerEventData;
Q_DECLARE_INTERFACE(ServerEventData, "net.horus.ServerEventData/1.0");
#endif
#ifdef HORUS_CLIENT
typedef EventData ClientEventData;
Q_DECLARE_INTERFACE(ClientEventData, "net.horus.ClientEventData/1.0");
#endif

#endif // EVENTDATA_H
