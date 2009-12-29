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
#ifndef ATTENDANCEDATABASEPLUGIN_H
#define ATTENDANCEDATABASEPLUGIN_H

#include <QHash>
#include "../../AttendanceDataPlugin.h"

class AttendanceDataBasePlugin : public AttendanceDataPlugin
{
	Q_OBJECT
#ifdef HORUS_SERVER
        Q_INTERFACES(ServerAttendanceDataPlugin)
#endif
#ifdef HORUS_CLIENT
        Q_INTERFACES(ClientAttendanceDataPlugin)
#endif

    friend class AttendanceDataBase;

    public:
                     AttendanceDataBasePlugin() {}
                     AttendanceData*	  newAttendance(UserData* parent, QDateTime *date, ScheduleData* schedule = 0);
                     AttendanceData*     attendance(quint32 attendanceId);
                     AttendanceData*     attendance(UserData *node);
    private:

	//Plugin
    public:
        inline const QString                    pluginName() const { return "Attendance Data Base"; }
        inline const QString                    pluginVersion() const { return "1"; }
        bool					canLoad() const;
        void					load();
        void					unload();
    public:
        inline const QString	dataType() const { return "Schedule"; }
#ifdef HORUS_CLIENT
        void                            dataHaveNewKey(Data*d, QDataStream& s);
#endif
#ifdef HORUS_SERVER
        QList<Data*>			datasForUpdate(UserData* user, QDateTime date);
#endif
    protected:
        //! Return the pointer to the Data with a his unique key read in the stream
            Data*					dataWithKey(QDataStream& s);
};

#endif // ATTENDANCEDATABASEPLUGIN_H
