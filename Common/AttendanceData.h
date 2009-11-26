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
