#ifndef EVENTDATABASE_H
#define EVENTDATABASE_H

#ifdef HORUS_SERVER
    #include <QtSql>
#endif
#ifdef HORUS_CLIENT
    #include <QVariant>
#endif
#include <QByteArray>
#include <QDateTime>
#include "../../Defines.h"
#include "../../EventData.h"
#include "EventDataBasePlugin.h"

class EventDataBase : public EventData
{
	Q_OBJECT
#ifdef HORUS_SERVER
	Q_INTERFACES(ServerEventData)
#endif
#ifdef HORUS_CLIENT
	Q_INTERFACES(ClientEventData)
#endif

  friend class			EventDataBasePlugin;

private:
						EventDataBase(TreeData* node, EventDataBasePlugin* plugin);
	inline				~EventDataBase() {}

	QDateTime			_startTime;
	QDateTime			_endTime;
	TreeData*			_node;


	// INTERFACE EventData
public:
	inline QDateTime	startTime() const { return _startTime; }
	inline void			setStartTime(const QDateTime& time) { _startTime = time; }
	inline QDateTime	endTime() const { return _endTime; }
	inline void			setEndTime(const QDateTime& time) { _endTime = time; }
	inline QDateTime	duration() const { return QDateTime::fromTime_t(_endTime.toTime_t() - _startTime.toTime_t()); }
	inline void			setDuration(const QDateTime& time) { _endTime = QDateTime::fromTime_t(_startTime.toTime_t() + time.toTime_t()); }
	inline TreeData*	node() const { return _node; }


	//INTERFACE Data
public:
	void				keyToStream(QDataStream& s);
	void				dataToStream(QDataStream& s) const;
	void				dataFromStream(QDataStream& s);

	QDebug				operator<<(QDebug debug) const;

#ifdef HORUS_CLIENT
	QVariant			data(int column, int role = Qt::DisplayRole) const;
#endif
#ifdef HORUS_SERVER
	quint8				serverRead();
	quint8				serverCreate();
	quint8				serverSave();
	quint8				serverRemove();
#endif
};

#endif // EVENTDATABASE_H
