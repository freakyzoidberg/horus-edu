/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
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
#include <QDate>
#include "../../Defines.h"
#include "../../AttendanceData.h"
#include "AttendanceDataBasePlugin.h"
#include "../../UserData.h"
#include "../../ScheduleData.h"

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
        AttendanceDataBase(quint32 id, AttendanceDataBasePlugin* plugin);
        inline                                                          ~AttendanceDataBase() {}

//        quint32                                                             _idUser;
//        quint32                                                             _idSchedule;
        quint32                                                             _type;
        QTime                                                               _startTime;
        QTime                                                               _endTime;
        QDate                                                           _date;
        UserData                                                        *_user;
        ScheduleData                                                    *_schedule;

        // INTERFACE AttendanceData
public:
        inline quint32                      id() const { return _id; }
        inline QDate    		date() const { return _date; }
        inline void			setDate(const QDate& date) { _date = date; }
        inline QTime                    endTime() const { return _endTime; }
        inline void			setEndTime(const QTime& e) { _endTime = e; }
        inline QTime                    startTime() const { return _startTime; }
        inline void			setStartTime(const QTime& s) { _startTime = s; }
//        inline quint32                      idUser() const { return _idUser; }
//        inline void			setIdUser(const int user) {_idUser = user; }
//        inline quint32                      idSchedule() const { return _idSchedule; }
//        inline void			setIdSchedule(const int event) { _idSchedule = event; }
        inline void                     setType(const int type) { _type = type; }
        inline quint32                      type() const { return _type; }
        inline void                     setUser(UserData *user) { _user = user; }
        inline UserData                 *user() const { return _user; }
        inline void                     setSchedule(ScheduleData *schedule) { _schedule = schedule; }
        inline const ScheduleData       *schedule() const { return _schedule; }


	//INTERFACE Data
public:
        void				keyToStream(QDataStream& s) const;
	void				dataToStream(QDataStream& s) const;
	void				dataFromStream(QDataStream& s);
        //bool				canChange(UserData* user) const;
        bool				canAccess(UserData* user) const;
	QDebug				operator<<(QDebug debug) const;
        const QList<Data*>              dependsOfCreatedData() const;

#ifdef HORUS_SERVER
public:
	quint8				serverRead();
	quint8				serverCreate();
	quint8				serverSave();
	quint8				serverRemove();
#endif
};

#endif // ATTENDANCEDATABASE_H
