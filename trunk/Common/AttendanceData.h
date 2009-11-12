#ifndef ATTENDANCEDATA_H
#define ATTENDANCEDATA_H

#include "Data.h"
#include "AttendanceDataPlugin.h"

class AttendanceData : public Data
{
	Q_OBJECT
#ifdef HORUS_SERVER
	Q_INTERFACES(ServerData)
#endif
#ifdef HORUS_CLIENT
	Q_INTERFACES(ClientData)
#endif

public:
        virtual int                     id() const = 0;
        virtual QDateTime		date() const = 0;
        virtual void			setDate(const QDateTime& date) = 0;
        virtual int     		idUser() const = 0;
        virtual void			setIdUser(const int user) = 0;
        virtual int     		idEvent() const = 0;
        virtual void			setIdEvent(const int event) = 0;
        virtual void                    setType(const int type) = 0;
        virtual int                     type() const = 0;

protected:
        inline				AttendanceData(AttendanceDataPlugin* plugin) : Data(plugin) { }
        inline				~AttendanceData() {}
};

#ifdef HORUS_SERVER
typedef AttendanceData ServerAttendanceData;
Q_DECLARE_INTERFACE(ServerAttendanceData, "net.horus.ServerAttendanceData/1.0");
#endif
#ifdef HORUS_CLIENT
typedef AttendanceData ClientAttendanceData;
Q_DECLARE_INTERFACE(ClientAttendanceData, "net.horus.ClientAttendanceData/1.0");
#endif

#endif // ATTENDANCEDATA_H
