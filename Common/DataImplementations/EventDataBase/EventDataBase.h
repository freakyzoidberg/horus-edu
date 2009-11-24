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
	~EventDataBase() {}

	QDateTime			_startTime;
	QDateTime			_endTime;
	QString				_comment;
	TreeData*			_node;


	// INTERFACE EventData
public:
	inline QDateTime	startTime() const					{ return _startTime; }
	inline void			setStartTime(const QDateTime& time)	{ QMutexLocker M(&mutex); _startTime = time; }
	inline QDateTime	endTime() const						{ return _endTime; }
	inline void			setEndTime(const QDateTime& time)	{ QMutexLocker M(&mutex); _endTime = time; }
	inline QString		comment() const						{ return _comment; }
	inline void			setComment(const QString& comment)	{ QMutexLocker M(&mutex); _comment = comment; }
	inline TreeData*	node() const						{ return _node; }


	//INTERFACE Data
public:
	void				keyToStream(QDataStream& s) const;
	void				dataToStream(QDataStream& s) const;
	void				dataFromStream(QDataStream& s);

	bool				canChange(UserData* user) const;
	bool				canAccess(UserData* user) const;

	const QList<Data*>	dependsOfCreatedData() const;

	QDebug				operator<<(QDebug debug) const;

#ifdef HORUS_CLIENT
	QVariant			data(int column, int role = Qt::DisplayRole) const;
#endif
#ifdef HORUS_SERVER
public:
	quint8				serverRead();
	quint8				serverCreate();
	quint8				serverSave();
	quint8				serverRemove();
#endif
};

#endif // EVENTDATABASE_H
