#ifndef ATTENDANCEDATABASE_H
#define ATTENDANCEDATABASE_H

#ifdef HORUS_SERVER
    #include <QtSql>
#endif
#ifdef HORUS_CLIENT
    #include <QVariant>
#endif
#include <QByteArray>
#include <QDateTime>
#include "../../Defines.h"
#include "../../AttendanceData.h"
#include "AttendanceDataBasePlugin.h"
#include "../../UserData.h"
#include "../../EventData.h"

class AttendanceDataBase : public AttendanceData
{
	Q_OBJECT
#ifdef HORUS_SERVER
        Q_INTERFACES(ServerAttendanceData)
#endif
#ifdef HORUS_CLIENT
        Q_INTERFACES(ClientAttendanceData)
#endif

  friend class                          AttendanceDataBasePlugin;

private:
										AttendanceDataBase(QList<EventData *> events, UserData *user, AttendanceDataBasePlugin* plugin);
		inline							~AttendanceDataBase() {}

        int                             _id;
        int                             _idUser;
        int                             _idEvent;
        int                             _type;
        QDateTime                       _date;
		UserData						*_user;
		QList<EventData *>				_events;

        // INTERFACE AttendanceData
public:
        inline int                      id() const { return _id; }
        inline QDateTime		date() const { return _date; }
		inline void				setDate(const QDateTime& date) { _date = date; }
        inline int                      idUser() const { return _idUser; }
        inline void			setIdUser(const int user) {_idUser = user; }
        inline int                      idEvent() const { return _idEvent; }
        inline void			setIdEvent(const int event) { _idEvent = event; }
        inline void                     setType(const int type) { _type = type; }
        inline int                      type() const { return _type; }
		inline void                     setUser(UserData *user) { _user = user; }
		inline int                      user() const { return _user; }
		inline void                     setEvents(const QList<EventData *> events) { _events = events; }
		inline int                      events() const { return _events; }


	//INTERFACE Data
public:
	void				keyToStream(QDataStream& s);
	void				dataToStream(QDataStream& s) const;
	void				dataFromStream(QDataStream& s);

	QDebug				operator<<(QDebug debug) const;

#ifdef HORUS_CLIENT
	QVariant			data(int column, int role = Qt::DisplayRole) const;
public slots:
	void				create();
#endif
#ifdef HORUS_SERVER
public:
	quint8				serverRead();
	quint8				serverCreate();
	quint8				serverSave();
	quint8				serverRemove();
#endif
};

#endif // ATTENDANCEDATABASE_H
