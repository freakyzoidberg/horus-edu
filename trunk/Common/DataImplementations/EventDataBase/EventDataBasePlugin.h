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

        EventData*			newEvent(TreeData* parent, QString name, UserData* user = 0);
        EventData*			nodeEvent(quint32 nodeId);
        EventData*			nodeEvent(TreeData* node);
	QList<EventData*>		nodeEvents(TreeData* node, const QDateTime from = QDateTime(), const QDateTime to = QDateTime());
	QList<EventData*>		userEvents(UserData* user, const QDateTime from = QDateTime(), const QDateTime to = QDateTime());

private:
        void				recursiveTreeSearch(QList<EventData*>& list, TreeData* node, const QDateTime& from, const QDateTime& to);

	QList<Data*>			_allEvents;


	//Plugin
public:
	inline const QString	pluginName() const { return "Event Data Base"; }
	inline const QString	pluginVersion() const { return "0.1"; }



	//DataPlugin
public:
	inline const QString	dataType() const { return "Event"; }
	QList<Data*>			allDatas() const { return _allEvents; }
#ifdef HORUS_SERVER
	void					loadData();
	QList<Data*>			datasForUpdate(UserData* user, QDateTime date);
#endif
protected:
    //! Return the pointer to the Data with a his unique key read in the stream
	Data*					dataWithKey(QDataStream& s);
};

#endif // EVENTDATABASEPLUGIN_H
