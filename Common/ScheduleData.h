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
#ifndef SCHEDULEDATA_H
#define SCHEDULEDATA_H

#include "Data.h"
#include "ScheduleDataPlugin.h"
#include "DataImplementations\ScheduleDataBase\ScheduleItem.h"

class ScheduleData : public Data
{
	Q_OBJECT
#ifdef HORUS_SERVER
	Q_INTERFACES(ServerData)
#endif
#ifdef HORUS_CLIENT
	Q_INTERFACES(ClientData)
#endif

public:
        virtual QDate                   startDate() const = 0;
        virtual void			setStartDate(const QDate& date) = 0;
        virtual QDate                   endDate() const = 0;
        virtual void			setEndDate(const QDate& date) = 0;
        virtual QList<ScheduleItem* >    scheduleEvents() const = 0;
        virtual void			addEvent(ScheduleItem* event) = 0;
        virtual void			removeEvent(ScheduleItem* event) = 0;
	virtual TreeData*		node() const = 0;

protected:
        inline					ScheduleData(ScheduleDataPlugin* plugin) : Data(plugin) { }
        virtual inline			~ScheduleData() {}
};

#ifdef HORUS_SERVER
typedef ScheduleData ServerScheduleData;
Q_DECLARE_INTERFACE(ServerScheduleData, "net.horus.ServerScheduleData/1.0");
#endif
#ifdef HORUS_CLIENT
typedef ScheduleData ClientScheduleData;
Q_DECLARE_INTERFACE(ClientScheduleData, "net.horus.ClientScheduleData/1.0");
#endif

#endif // SCHEDULEDATA_H
