#ifndef EVENTDATABASEPLUGIN_H
#define EVENTDATABASEPLUGIN_H

#include <QHash>
#include "../../EventDataPlugin.h"

class EventDataBasePlugin : public EventDataPlugin
{
	Q_OBJECT
#ifdef HORUS_SERVER
	Q_INTERFACES(ServerEventDataPlugin)
#endif
#ifdef HORUS_CLIENT
	Q_INTERFACES(ClientEventDataPlugin)
#endif

  friend class EventDataBase;

public:
								EventDataBasePlugin() {}
	EventData*					getEvent(quint32 nodeId);
	EventData*					getEvent(TreeData* node);
private:
	QHash<TreeData*,EventData*>	events;

	//Plugin
public:
	inline const QString		pluginName() const { return "Event Data Base"; }
	inline const QString		pluginVersion() const { return "0.1"; }


	//DataPlugin
public:
	inline const QString		getDataType() const { return "Event"; }
	QList<Data*>				allDatas() const;
#ifdef HORUS_SERVER
	void						loadData();
	void						userConnected(UserData* user, QDateTime date);
#endif
protected:
    //! Return the pointer to the Data with a his unique key read in the stream
	Data*						getDataWithKey(QDataStream& s);
};

#endif // TREEDATABASEPLUGIN_H
